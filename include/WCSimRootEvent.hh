#ifndef WCSim_RootEvent
#define WCSim_RootEvent

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//    WCSim_RootEvent                                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TClonesArray.h"
#include <string>
#include <vector>
#include <iostream>
#include "jhfNtuple.h"
//#include <map>
//#include "G4Transform3D.hh"

// #include "WCSimDetectorConstruction.hh"
#include "WCSimEnumerations.hh"

class TDirectory;


class WCSimRootTrack : public TObject {

private:

  // See jhfNtuple.h for the meaning of these data members:
  Int_t   fIpnu;        
  Int_t   fFlag;        
  Double_t fM;
  Double_t fP;
  Double_t fE;
  Int_t   fStartvol;
  Int_t   fStopvol;
  Double_t fDir[3];
  Double_t fPdir[3];
  Double_t fStop[3];
  Double_t fStart[3];
  Int_t fParenttype;
  Double_t fTime;
  Int_t fId;

public:
  WCSimRootTrack() {}
  WCSimRootTrack(Int_t ipnu, 
		  Int_t flag, 
		  Double_t m,
		  Double_t p,
		  Double_t E,
		  Int_t startvol, 
		  Int_t stopvol, 
		  Double_t dir[3],
		  Double_t pdir[3],
		  Double_t stop[3],
		  Double_t start[3],
		  Int_t parenttype,
		 Double_t time,Int_t id);
  virtual ~WCSimRootTrack() { }
  bool CompareAllVariables(const WCSimRootTrack * c) const;

  Int_t     GetIpnu() const { return fIpnu;}
  Int_t     GetFlag() const { return fFlag;}
  Double_t  GetM() const { return fM;}
  Double_t  GetP() const { return fP;}
  Double_t  GetE() const { return fE;}
  Int_t     GetStartvol() const { return fStartvol;}
  Int_t     GetStopvol() const { return fStopvol;}
  Double_t  GetDir(Int_t i=0) const {return (i<3) ? fDir[i] : 0;}
  Double_t  GetPdir(Int_t i=0) const {return (i<3) ? fPdir[i] : 0;}
  Double_t  GetStop(Int_t i=0) const {return (i<3) ? fStop[i] : 0;}
  Double_t  GetStart(Int_t i=0) const {return (i<3) ? fStart[i] : 0;}
  Int_t     GetParenttype(/*Int_t i=0*/) const {return fParenttype;}
  Double_t  GetTime() const { return fTime;}
  Int_t     GetId() const {return fId;}

  ClassDef(WCSimRootTrack,1)  
};


//////////////////////////////////////////////////////////////////////////


class WCSimRootCherenkovHit : public TObject {

private:
  Int_t fTubeID;
  Int_t fTotalPe[2];

public:
  WCSimRootCherenkovHit() {}
  WCSimRootCherenkovHit(Int_t tubeID,
			Int_t totalPe[2]);

  virtual ~WCSimRootCherenkovHit() { }

  bool CompareAllVariables(const WCSimRootCherenkovHit * c) const;

  Int_t GetTubeID()       const { return fTubeID;}
  Int_t GetTotalPe(int i) const { return (i<2) ? fTotalPe[i]: 0;}

  ClassDef(WCSimRootCherenkovHit,1)  
};

class WCSimRootCherenkovHitTime : public TObject {

private:
  // See jhfNtuple.h for the meaning of these data members:
  Double_t fTruetime;
  Int_t   fPrimaryParentID;

public:
  WCSimRootCherenkovHitTime() {}
  WCSimRootCherenkovHitTime(Double_t truetime,
			    Int_t   primaryParentID);
  virtual ~WCSimRootCherenkovHitTime() { }
  bool CompareAllVariables(const WCSimRootCherenkovHitTime * c) const;

  Double_t  GetTruetime() const { return fTruetime;}
  Int_t     GetParentID() const { return fPrimaryParentID;}

  ClassDef(WCSimRootCherenkovHitTime,1)  
};


//////////////////////////////////////////////////////////////////////////


class WCSimRootCherenkovDigiHit : public TObject {

private:
  // See jhfNtuple.h for the meaning of these data members:
  Double_t fQ;
  Double_t fT;
  Int_t fTubeId;
  std::vector<int> fPhotonIds;

public:
  WCSimRootCherenkovDigiHit() {}
  WCSimRootCherenkovDigiHit(Double_t q, Double_t t, Int_t tubeid, std::vector<int> photon_ids);

  virtual ~WCSimRootCherenkovDigiHit() { }
  bool CompareAllVariables(const WCSimRootCherenkovDigiHit * c) const;

  void SetT(double t) { fT = t; }
  Double_t    GetQ() const { return fQ;}
  Double_t    GetT() const { return fT;}
  Int_t       GetTubeId() const { return fTubeId;}
  std::vector<int> GetPhotonIds() const { return fPhotonIds; }

  ClassDef(WCSimRootCherenkovDigiHit,2)  
};


//////////////////////////////////////////////////////////////////////////

class WCSimRootEventHeader {

private:
  Int_t   fEvtNum;
  Int_t   fRun;
  Int_t   fDate;
  Int_t   fSubEvtNumber;

public:
  WCSimRootEventHeader() : fEvtNum(0), fRun(0), fDate(0), fSubEvtNumber(1) { }
  virtual ~WCSimRootEventHeader() { }
  bool CompareAllVariables(const WCSimRootEventHeader * c) const;
  void   Set(Int_t i, Int_t r, Int_t d, Int_t s=1) { fEvtNum = i; fRun = r; fDate = d; fSubEvtNumber = s;}
  void SetDate(Int_t d) { fDate=d; }
  Int_t  GetEvtNum() const { return fEvtNum; }
  Int_t  GetRun() const { return fRun; }
  Int_t  GetDate() const { return fDate; }
  Int_t GetSubEvtNumber() const { return fSubEvtNumber;}
  

   ClassDef(WCSimRootEventHeader,2)  //WCSimRootEvent Header
};

//////////////////////////////////////////////////////////////////////////

class WCSimRootPi0 : public TObject {
  // this is a class used specifically for Pi0 events

private:
  Double_t fPi0Vtx[3];
  Int_t   fGammaID[2];
  Double_t fGammaE[2];
  Double_t fGammaVtx[2][3];

public:
  WCSimRootPi0() {}

  virtual ~WCSimRootPi0() { }
  bool CompareAllVariables(const WCSimRootPi0 * c) const;

  void Set(Double_t pi0Vtx[3],
	   Int_t   gammaID[2],
	   Double_t gammaE[2],
	   Double_t gammaVtx[2][3]);

  Double_t  GetPi0Vtx(int i)          const { return (i<3) ? fPi0Vtx[i]: 0;}
  Int_t    GetGammaID(int i)          const { return (i<2) ? fGammaID[i]: 0;}
  Double_t  GetGammaE(int i)          const { return (i<2) ? fGammaE[i]: 0;}
  Double_t  GetGammaVtx(int i, int j) const { return fGammaVtx[i][j];}

  ClassDef(WCSimRootPi0,1)
};

//////////////////////////////////////////////////////////////////////////

class WCSimRootTrigger : public TObject {

private:
  WCSimRootEventHeader    fEvtHdr;  // The header
  // See jhfNtuple.h for the meaning of these data members:
  Int_t                fMode;
  Int_t                fNvtxs;
  Int_t                fVtxsvol[MAX_N_PRIMARIES];
  Double_t             fVtxs[MAX_N_PRIMARIES][3];
  Int_t                fVecRecNumber;       // "info event" number in inputvectorfile 
  Int_t                fJmu;
  Int_t                fJp;

  WCSimRootPi0        fPi0;                // Pi0 info (default = not used)

  Int_t                fNpar;               // Number of particles
  Int_t                fNtrack;             // Number of tracks in the array
  Int_t                fNtrack_slots;       // Number of slots in the tracks array. This is potentially more than fNtrack (i.e. if any tracks have been removed that aren't at the very start/end)
  TClonesArray         *fTracks;            //-> Array of WCSimRootTracks 

  Int_t                fNumTubesHit;        // Number of tubes hit
  Int_t                fNcherenkovhits;      // Number of hits in the array
  TClonesArray         *fCherenkovHits;      //-> Array of WCSimRootCherenkovHits

  Int_t                fCherenkovHitCounter;
  Int_t                fNcherenkovhittimes;      // Number of hits in the array
  TClonesArray         *fCherenkovHitTimes;      //-> Array of WCSimRootCherenkovHits

  Int_t                fNumDigitizedTubes;  // Number of digitized tubes
  Int_t                fNcherenkovdigihits;  // Number of digihits in the array
  Int_t                fNcherenkovdigihits_slots;  // Number of slots in the digihits array. This is potentially more than fNcherenkovdigihits (i.e. if any digihits have been removed that aren't at the very start/end)
  Double_t             fSumQ;
  TClonesArray         *fCherenkovDigiHits;  //-> Array of WCSimRootCherenkovDigiHit's

  TriggerType_t        fTriggerType;         // Trigger algorithm that created this trigger
  std::vector<Double_t> fTriggerInfo;        // Information about how it passed the trigger (e.g. how many hits in the NDigits window)

  bool IsZombie;

public:
  WCSimRootTrigger();
  WCSimRootTrigger(int, int);
  virtual ~WCSimRootTrigger();
  WCSimRootTrigger & operator=(const WCSimRootTrigger & in);
  bool CompareAllVariables(const WCSimRootTrigger * c, bool deep_comparison = false) const;
  
  void Initialize();

  void          Clear(Option_t *option ="");
  static void   Reset(Option_t *option ="");

  void          SetHeader(Int_t i, Int_t run, Int_t date,Int_t subevtn=1);
  void          SetTriggerInfo(TriggerType_t trigger_type, std::vector<Double_t> trigger_info);
  bool          IsASubEvent() {  return (fEvtHdr.GetSubEvtNumber()>=1); }
  void          SetMode(Int_t i) {fMode = i;}
  void          SetNvtxs(Int_t i) {fNvtxs = i;}
  void          SetVtxvol(Int_t i) {fVtxsvol[0] = i;}
  void          SetVtxsvol(Int_t i, Int_t v) {fVtxsvol[i] = v;}
  void          SetVtx(Int_t i, Double_t f) {fNvtxs=1; fVtxs[0][i] = ( (i<3) ? f : 0);}
  void          SetVtxs(Int_t n, Int_t i, Double_t f) {fVtxs[n][i]= ( (i<3) ? f : 0);}
  void          SetVecRecNumber(Int_t i) {fVecRecNumber = i;}
  void          SetJmu(Int_t i) {fJmu = i;}
  void          SetJp(Int_t i) {fJp = i;}
  void          SetNpar(Int_t i) {fNpar = i;}
  void          SetNumTubesHit(Int_t i) {fNumTubesHit = i;}
  void          SetSumQ(Double_t x){fSumQ = x;}
  void          SetNumDigitizedTubes(Int_t i) {fNumDigitizedTubes = i;}
  void          SetPi0Info(Double_t pi0Vtx[3], 
			   Int_t   gammaID[2], 
			   Double_t gammaE[2],
			   Double_t gammaVtx[2][3]);

  WCSimRootEventHeader *GetHeader()               {return &fEvtHdr; }
  const WCSimRootEventHeader * GetHeader()     const {return &fEvtHdr; }
  WCSimRootPi0       *GetPi0Info()                 {return &fPi0; }
  const WCSimRootPi0         * GetPi0Info()    const {return &fPi0; }
  Int_t               GetMode()               const {return fMode;}
  Int_t               GetVtxvol()             const {return fVtxsvol[0];}
  Double_t            GetVtx(Int_t i=0)             {return (i<3) ? fVtxs[0][i]: 0;}
  Int_t               GetNvtxs()             const {return fNvtxs;}
  Int_t               GetVtxsvol(Int_t i)             const {return fVtxsvol[i];}
  Double_t            GetVtxs(Int_t n, Int_t i=0)     const {return (i<3) ? fVtxs[n][i]: 0;}
  Int_t               GetVecRecNumber()       const {return fVecRecNumber;}
  Int_t               GetJmu()                const {return fJmu;}
  Int_t               GetJp()                 const {return fJp;}
  Int_t               GetNpar()               const {return fNpar;}
  Int_t               GetNumTubesHit()        const {return fNumTubesHit;}
  Int_t               GetNumDigiTubesHit()    const {return fNumDigitizedTubes;}
  Int_t               GetNtrack()             const {return fNtrack; }
  Int_t               GetNtrack_slots()       const {return fTracks->GetLast() + 1; } //don't use fNtrack_slots directly as it doesn't take into account automatic TClonesArray shortening when tracks at start/end are removed
  Int_t               GetNcherenkovhits()     const {return fNcherenkovhits; }
  Int_t               GetNcherenkovhittimes() const {return fNcherenkovhittimes;}
  Int_t               GetNcherenkovdigihits() const {return fNcherenkovdigihits;}
  Int_t               GetNcherenkovdigihits_slots() const {return fCherenkovDigiHits->GetLast() + 1; } //don't use fNcherenkovdigihits_slots directly as it doesn't take into account automatic TClonesArray shortening when digits at start/end are removed
  Double_t            GetSumQ()               const { return fSumQ;}
  TriggerType_t       GetTriggerType()        const { return fTriggerType;}
  std::vector<Double_t> GetTriggerInfo()       const { return fTriggerInfo;}

  WCSimRootTrack         *AddTrack(Int_t ipnu, 
				   Int_t flag, 
				   Double_t m,
				   Double_t p,
				   Double_t E,
				   Int_t startvol, 
				   Int_t stopvol, 
				   Double_t dir[3],
				   Double_t pdir[3],
				   Double_t stop[3],
				   Double_t start[3],
				   Int_t parenttype,
				   Double_t time,
				   Int_t id);

  WCSimRootTrack * AddTrack   (WCSimRootTrack * track);
  WCSimRootTrack * RemoveTrack(WCSimRootTrack * track);

  TClonesArray        *GetTracks() const {return fTracks;}

  WCSimRootCherenkovHit   *AddCherenkovHit(Int_t                tubeID,
					  std::vector<Double_t> truetime,
					  std::vector<Int_t>   primParID);
  TClonesArray        *GetCherenkovHits() const {return fCherenkovHits;}
  TClonesArray        *GetCherenkovHitTimes() const {return fCherenkovHitTimes;}

  WCSimRootCherenkovDigiHit   *AddCherenkovDigiHit(Double_t q,
						   Double_t t,
						   Int_t tubeid,
						   std::vector<int> photon_ids);
//  WCSimRootCherenkovDigiHit   *AddCherenkovDigiHit(Double_t q,
//						  Double_t t,
//						  Int_t tubeid,
 //                                                 Double_t sumq);
  WCSimRootCherenkovDigiHit * AddCherenkovDigiHit(WCSimRootCherenkovDigiHit * digit);
  WCSimRootCherenkovDigiHit * RemoveCherenkovDigiHit(WCSimRootCherenkovDigiHit * digit);
  TClonesArray            *GetCherenkovDigiHits() const {return fCherenkovDigiHits;}

  ClassDef(WCSimRootTrigger,3) //WCSimRootEvent structure
};


class WCSimRootEvent : public TObject {
public:
  WCSimRootEvent();
  virtual ~WCSimRootEvent();
  WCSimRootEvent & operator=(const WCSimRootEvent & in);
  bool CompareAllVariables(const WCSimRootEvent * c, bool deep_comparison = false) const;

  void          Clear(Option_t *option ="");
  static void   Reset(Option_t *option ="");
  Int_t GetCurrentIndex() { return Current;}

        WCSimRootTrigger * GetTrigger(int number)       { return (WCSimRootTrigger*) fEventList->At(number);}
  const WCSimRootTrigger * GetTrigger(int number) const { return (WCSimRootTrigger*) fEventList->At(number);}

  Int_t GetNumberOfEvents() const { return fEventList->GetEntries();}
  Int_t GetNumberOfSubEvents() const { return (fEventList->GetEntries()-1);}
  bool HasSubEvents() { return  (fEventList->GetEntries() > 1); }

  void AddSubEvent() { 
    // be sure not to call the default constructor BUT the actual one
    ++Current;
    if ( Current > 9 ) fEventList->Expand(150);
    int num = ((WCSimRootTrigger*)fEventList->At(0))->GetHeader()->GetEvtNum();
    new((*fEventList)[Current]) WCSimRootTrigger(num,Current);
  }
  
  void Initialize();

  void ReInitialize() { 
    Current = 0;
    fEventList->Clear();
    new((*fEventList)[Current]) WCSimRootTrigger(-99,Current);
  }

private:
  TClonesArray* fEventList;
  Int_t Current;                      //!               means transient, not writable to file
  ClassDef(WCSimRootEvent,2)
};


#endif
