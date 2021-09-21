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
// $Id: HistoManager.hh,v 1.1 2010-09-21 17:55:58 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HistoManager_h
#define HistoManager_h

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4UIcommand.hh"
#include "G4SystemOfUnits.hh"

//std c- includes
#include <iostream>
#include <time.h>
#include <vector>

//root includes
//#include "TFile.h"
//#include "TDirectory.h"
//#include "TTree.h"
//#include "TH1F.h"
//#include "TH2F.h"
class TFile;
class TH1F;

#include "FKHit.hh"
#include "B1DetectorConstruction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:

    HistoManager();
   ~HistoManager();

    static HistoManager* GetInstance();

    void book();

    void SaveFile();
    void CloseFile();
    
    void SetWriteHisto(G4bool histo);
    void SetResultsFile(G4String filename);

    void CreateHistograms();

    void Fill1DEdep(G4double Edep);
    //void FillTree();

  private:

    G4String    fResFilename;
    G4bool      fWriteHisto;

    TFile       *f;
    TH1F        *pH1Edep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

