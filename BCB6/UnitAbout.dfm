object FormAbout: TFormAbout
  Left = 500
  Top = 219
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'About'
  ClientHeight = 183
  ClientWidth = 248
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = OnCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 248
    Height = 183
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object LabelAuthor: TLabel
      Left = 8
      Top = 109
      Width = 233
      Height = 44
      Alignment = taCenter
      AutoSize = False
      Caption = 'Author'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Transparent = True
      WordWrap = True
    end
    object LabelVersion: TLabel
      Left = 8
      Top = 90
      Width = 233
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Version'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Transparent = True
      WordWrap = True
    end
    object Label4: TLabel
      Left = 0
      Top = 8
      Width = 241
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'TicketSolver'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      WordWrap = True
    end
    object LabelDescription: TLabel
      Left = 8
      Top = 29
      Width = 233
      Height = 52
      AutoSize = False
      Caption = 'Description'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Transparent = True
      WordWrap = True
    end
    object Button1: TButton
      Left = 86
      Top = 156
      Width = 75
      Height = 25
      Cancel = True
      Caption = #1054#1050
      Default = True
      ModalResult = 1
      TabOrder = 0
    end
  end
end
