//---------------------------------------------------------------------------

#ifndef UnitAboutH
#define UnitAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormAbout : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel2;
  TButton *Button1;
        TLabel *LabelAuthor;
        TLabel *LabelVersion;
        TLabel *Label4;
        TLabel *LabelDescription;
  void __fastcall OnCreate(TObject *Sender);

private:	// User declarations
  String Version;
  String Description;
  String Author;

public:		// User declarations
  __fastcall TFormAbout(TComponent* Owner, String Version, String Description, String Author);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//---------------------------------------------------------------------------
#endif
