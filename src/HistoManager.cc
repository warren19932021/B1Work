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
// HistoManager.cc,v 1.0 2013-04-23 14:00:00 Toni Kögler$

//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4String.hh"

//root includes
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TROOT.h"

//std c- includes
#include <iostream>
#include <time.h>



using namespace std;

//static HistoManager* instance = 0;

////////////////////////////////////////////////////////////////////////////////
HistoManager::HistoManager()
    : fWriteHisto(true),
      fResFilename("results/out.root")
{  // Creating the analysis factory
     G4cout << " HistoManager::HistoManager() :"
           << "  creating Histograms."
           << G4endl;
}

HistoManager::~HistoManager()
{
    if (!fWriteHisto) return;
    //remove histograms from memory
    delete pH1Edep;
}
////////////////////////////////////////////////////////////////////////////////
//______________________________________________________________________________
void HistoManager::book()
{//open the root file and create a directory structure in it
 // This method is called at the beginning of a run.
    //G4cout << "******************************************" << G4endl
    //       << "* DEBUG: HistoManager::book() is called! *" << G4endl
    //       << "******************************************" << G4endl;

    if (!fWriteHisto)
        return;

    //ROOT::EnableThreadSafety();
    f = TFile::Open(fResFilename.c_str(), "RECREATE");

    CreateHistograms();

    G4cout << "\n----> Histogram file is opened in " << fResFilename << G4endl;

}

//______________________________________________________________________________
void HistoManager::SaveFile()
{
    if (fWriteHisto) {   
        G4cout << "Write histograms to TFile" << G4endl;
        //f->cd();
        pH1Edep->Write("Edep", TObject::kOverwrite);
        //pH1Edep->Write();
    }

    if (fWriteHisto) { // (WriteTTree || fWriteHisto)
        G4cout << "\n----> Saving progress..."  << G4endl;
        //f->Save();
    }

}

//______________________________________________________________________________
void HistoManager::CloseFile()
{
    if (!fWriteHisto)
        return;
        
    SaveFile();
    f->Close();      // and closing the tree (and the file)
    G4cout << "\n----> Histogram file closed"  << G4endl;

}

//______________________________________________________________________________
void HistoManager::SetWriteHisto(G4bool histo)
{   fWriteHisto = histo;
    if (fWriteHisto)
        G4cout << "Enable Histogramming!" << G4endl;
    else
        G4cout << "Disable Histogramming!" << G4endl;
}

//______________________________________________________________________________
void HistoManager::SetResultsFile(G4String filename)
{
    fResFilename = filename;
}

//______________________________________________________________________________
void HistoManager::CreateHistograms()
{//sets up all used histograms
    G4int nBinsX = 10000; G4double minX = 0.0, maxX = 2000.;

    G4String HistName =  "Edep";
    G4String HistTitle=  "Energy deposition in sensitive region";

    // define Histogram and set style attributes
    pH1Edep = new TH1F(HistName, HistTitle, nBinsX, minX, maxX);
    // x-axis
    pH1Edep->GetXaxis()->SetTitle("#font[12]{E} / keV");
    // y-axis
    pH1Edep->GetYaxis()->SetTitle("#font[12]{N}");
}
//______________________________________________________________________________
void HistoManager::Fill1DEdep(G4double Edep)
{
    G4cout << "Fill " << G4BestUnit(Edep, "Energy") << G4endl;
    pH1Edep->Fill(Edep / CLHEP::keV);
}
//______________________________________________________________________________
