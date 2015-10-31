//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner, String Version, String Description, String Author)
  : TForm(Owner),
    Version (Version),
    Description (Description),
    Author (Author)
{
//
//
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::OnCreate(TObject *Sender)
{
//
//
  LabelDescription->Caption = Description;
  LabelVersion->Caption = String ("Version ") + Version;
  LabelAuthor->Caption = String ("Author ") + Author;
}
//---------------------------------------------------------------------------


