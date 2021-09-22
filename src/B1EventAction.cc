//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "RunAction.hh"
#include "FKHit.hh"
#include "FKSD.hh"
#include "HistoManager.hh"

#include "G4UnitsTable.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(RunAction* runAction, HistoManager* histo)
: G4UserEventAction(),
fRunAction(runAction),
histoManager(histo)
{
  //fRunAction = runAction;
  //histoManager = histo;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{    
  //G4cout << "DEBUG: Begin of event action" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event* evt)
{   
    //G4cout << "DEBUG: End of event action" << G4endl;
    G4String HCName = "FKHitsCollection";
    FKHitsCollection *FK_HC;
    fFK_HCID = G4SDManager::GetSDMpointer()->GetCollectionID(HCName);
    // Get hits collection
    FK_HC = GetHitsCollection(fFK_HCID, evt);
    //get through all hits of this event
    G4int nofHits = FK_HC->entries();
    if (nofHits == 0) {
        //G4cout << "DEBUG: No hits. return. " << G4endl;
        return;
    }
    
    //G4cout << "DEBUG: event " << evt->GetEventID() << ", HC " << FK_HC->GetName() << ": " << nofHits << " hits" << G4endl;
    G4double totEdep = 0.0 * CLHEP::keV;
    for (G4int i = 0; i < nofHits; i++) {
        FKHit *hit = (*FK_HC)[i];
        //hit->Print();
        totEdep += hit->GetEdep();
        //G4cout << "total Edep: " << totEdep << G4endl;
    }
    G4cout << nofHits << " hits with total Edep " << G4BestUnit(totEdep, "Energy") << G4endl;
    
    // Fill Histogram...
    G4AnalysisManager::Instance()->FillH1(1, totEdep);
    //histoManager->Fill1DEdep(totEdep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FKHitsCollection* B1EventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
  FKHitsCollection* hitsCollection
    = static_cast<FKHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
