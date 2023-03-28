#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "WCSimDetectorConstruction.hh"
#include "WCSimPhysicsListFactory.hh"
#include "WCSimPhysicsListFactoryMessenger.hh"
#include "WCSimTuningParameters.hh"
#include "WCSimTuningMessenger.hh"
#include "WCSimPrimaryGeneratorAction.hh"
#include "WCSimEventAction.hh"
#include "WCSimRunAction.hh"
#include "WCSimStackingAction.hh"
#include "WCSimTrackingAction.hh"
#include "WCSimSteppingAction.hh"
#include "WCSimVisManager.hh"
#include "WCSimRandomParameters.hh"

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include <string>
#include <sstream>


namespace {     // Anonymous namespace for local helper functions and classes
  enum class WCSimExeMode {Batch, Interactive, Unknown};

  bool file_exists(const char * filename) {
    bool exists = access(filename, F_OK) != -1;
    if(!exists) {
      G4cerr << filename << " not found or inaccessible." << G4endl;
    }
    return exists;
  }

  std::string usage_statement(const std::string exename) {
    std::stringstream msg;
#ifdef G4UI_USE
    msg << "interactive usage: " << exename << " visualization_macro\n"
        << "    visualization_macro:  name of a macro file that sets up the visualization\n"
        << "An interactive UI will be launched after visualization_macro is executed.\n\n";
#else
    msg << "Not built for interactive use.\n\n";
#endif

    msg << "batch usage: " << exename << " steering_macro tuning_par_macro\n"
        << "    steering_macro:  name of main WCSim execution macro file\n"
        << "    tuning_par_macro:  name of a macro file containing only tuning parameter\n"
        << "        commands recognized by WCSimTuningMessenger\n";

    return msg.str();
  }
}


int main(int argc,char** argv)
{
  WCSimExeMode exemode = WCSimExeMode::Unknown;

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // get the pointer to the UI manager
  G4UImanager* UI = G4UImanager::GetUIpointer();

  // Set up the tuning parameters that need to be read before the detector
  //  construction is done
  WCSimTuningParameters* tuningpars = new WCSimTuningParameters();

  // Execute command for processing input macros
  const G4String execommand = "/control/execute ";

  // Check arguments, set execution mode and perform some prep.
  switch(argc) {
#ifdef G4UI_USE
    case 2 :    // Interactive mode with no command-line arguments
      exemode = WCSimExeMode::Interactive;
      G4cout << "Entering interactive mode after setup." << G4endl;
      G4cout << "Using default tuning parameters." << G4endl;
      break;
#endif

    case 3 :    // Batch mode with two command-line arguments
      // Check presence of input files
      if( file_exists(argv[1]) && file_exists(argv[2]) ) {
        exemode = WCSimExeMode::Batch;
        // Process tuning parameters
        G4cout << "Processing tuning parameter file " << argv[2] << G4endl;
        UI->ApplyCommand(execommand + G4String(argv[2]));
        break;
      }

    // Otherwise proceed to default exit condition
    default:    // Unrecognized number of valid command line arguments
      // Print usage statement
      G4cout << usage_statement(argv[0]) << G4endl;

      // Clean up
      delete runManager;

      // Exit.
      return -1;
  }

  // define random number generator parameters
  WCSimRandomParameters *randomparameters = new WCSimRandomParameters();

  // UserInitialization classes (mandatory)
  enum DetConfiguration {wfm=1,fwm=2};
  G4int WCSimConfiguration = fwm;

  WCSimDetectorConstruction* WCSimdetector = new 
    WCSimDetectorConstruction(WCSimConfiguration,tuningpars);

  runManager->SetUserInitialization(WCSimdetector);

  // Added selectable physics lists 2010-07 by DMW
  // Set up the messenger hooks here, initialize the actual list after loading jobOptions.mac
  WCSimPhysicsListFactory *physFactory = new WCSimPhysicsListFactory();

  // Currently, default physics list is set to FTFP_BERT
  // The custom WCSim physics list option is removed in versions later than WCSim1.6.0
  const char *WCSIMDIR = std::getenv("WCSIMDIR");
  if (!(WCSIMDIR && WCSIMDIR[0])) { // make sure it's non-empty
    WCSIMDIR = "."; // the "default" value
    G4cout << "Note: WCSIMDIR not set, assuming: " << WCSIMDIR << G4endl;
  }
  G4cout << "B.Q: Read" << Form("/control/execute %s/macros/jobOptions.mac",WCSIMDIR) << G4endl;
  file_exists(Form("%s/macros/jobOptions.mac",WCSIMDIR));
  UI->ApplyCommand(Form("/control/execute %s/macros/jobOptions.mac",WCSIMDIR));

  // Initialize the physics factory to register the selected physics.
  physFactory->InitializeList();
  runManager->SetUserInitialization(physFactory);

  // Visualization
  G4VisManager* visManager = new WCSimVisManager;
  visManager->Initialize();

  // Set user action classes
  WCSimPrimaryGeneratorAction* myGeneratorAction = new 
    WCSimPrimaryGeneratorAction(WCSimdetector);
  runManager->SetUserAction(myGeneratorAction);


  WCSimRunAction* myRunAction = new WCSimRunAction(WCSimdetector, randomparameters);

  //save all the options from WCSimTuningParameters & WCSimPhysicsListFactory
  //(set in tuning_parameters.mac & jobOptions*.mac)
  tuningpars->SaveOptionsToOutput(myRunAction->GetRootOptions());
  physFactory->SaveOptionsToOutput(myRunAction->GetRootOptions());

  runManager->SetUserAction(myRunAction);

  runManager->SetUserAction(new WCSimEventAction(myRunAction, WCSimdetector,
						 myGeneratorAction));
  runManager->SetUserAction(new WCSimTrackingAction);

  runManager->SetUserAction(new WCSimStackingAction(WCSimdetector));

  runManager->SetUserAction(new WCSimSteppingAction(myRunAction,WCSimdetector));

  // Initialize G4 kernel
  runManager->Initialize();

  switch(exemode) {
    case WCSimExeMode::Batch : {
      G4cout << "WE WILL EXECUTE " << argv[1] << " IN BATCH MODE" << G4endl;
      UI->ApplyCommand(execommand + G4String(argv[1]));
      break;
    }

    case WCSimExeMode::Interactive : {
#ifdef G4UI_USE
      // Launch the interactive UI
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      G4cout << "Running visualization initialization macro " << argv[1] << G4endl;
      UI->ApplyCommand(execommand + G4String(argv[1]));
      ui->SessionStart();

      // Clean it up on exit
      delete ui;
#else
      G4cerr << "SOMETHING IS WRONG.  Attempt to execute in interactive mode without being built for interactive mode." << G4endl;
#endif
      break;
    }

    case WCSimExeMode::Unknown : {
      G4cerr << "SOMETHING IS WRONG.  Attempt to execute in undefined mode." << G4endl;
    }
  }

  delete visManager;

  delete runManager;
  return 0;
}


