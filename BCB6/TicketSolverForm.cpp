//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TicketSolver.h"
#include "UnitAbout.h"
#include "TicketSolverForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTicketSolverMainForm *TicketSolverMainForm;
TicketSolver *ticketSolver = NULL;
//---------------------------------------------------------------------------
__fastcall TTicketSolverMainForm::TTicketSolverMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTicketSolverMainForm::BitBtnSolveClick(TObject *Sender)
{
  if (std::string (Edit1->Text.c_str ()).find_first_not_of ("0123456789") != std::string::npos) {
    std::string line = std::string ("Wrong argument ").append (Edit1->Text.c_str ()).append (", please enter only digits.");
    TicketSolverMainForm->Memo1->Lines->Add (line.c_str ());
    return;
  }

  //ticketSolver->SolveSingle (Edit1->Text.c_str ());
  ticketSolver->Solve (Edit1->Text.c_str ());
  const std::list <std::string> &log = ticketSolver->getLog ();
  for (std::list <std::string>::const_iterator it = log.begin (); it != log.end (); it++) {
    TicketSolverMainForm->Memo1->Lines->Add (it->c_str ());
  }
}
//---------------------------------------------------------------------------
void __fastcall TTicketSolverMainForm::FormCreate(TObject *Sender)
{
  ticketSolver = new TicketSolver ();
}
//---------------------------------------------------------------------------

void __fastcall TTicketSolverMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  delete ticketSolver;
  ticketSolver = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TTicketSolverMainForm::Memo1KeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if ((Key == 'A') && Shift.Contains (ssCtrl)) {
    Memo1->SelectAll();
    Key = 0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TTicketSolverMainForm::BitBtnAboutClick(TObject *Sender)
{
  try {
    std::string description = "";
    std::string version = "";
    std::string author = "";
    TicketSolver::getVersion (version, description, author);
    FormAbout = new TFormAbout (this, version.c_str (), description.c_str (), author.c_str ());
    if (FormAbout) {
      FormAbout->ShowModal ();
    }
  }
  __finally {
    if (FormAbout) {
      delete FormAbout;
      FormAbout = NULL;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TTicketSolverMainForm::Edit1KeyPress(TObject *Sender,
      char &Key)
{
  if (Key == VK_RETURN) {
    BitBtnSolveClick (Sender);
  }
}
//---------------------------------------------------------------------------

