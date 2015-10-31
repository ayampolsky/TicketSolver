//---------------------------------------------------------------------------

#ifndef TicketSolverFormH
#define TicketSolverFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTicketSolverMainForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Edit1;
        TBitBtn *BitBtnAbout;
        TBitBtn *BitBtnSolve;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall BitBtnAboutClick(TObject *Sender);
        void __fastcall BitBtnSolveClick(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TTicketSolverMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTicketSolverMainForm *TicketSolverMainForm;
//---------------------------------------------------------------------------
#endif
