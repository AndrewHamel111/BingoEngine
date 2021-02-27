unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ValEdit,
  ExtCtrls, ExtDlgs, Menus, Unit2, ;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    DescriptionBox: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    MainMenu1: TMainMenu;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem3: TMenuItem;
    MenuItem4: TMenuItem;
    TestLabel: TLabel;
    WordList: TListBox;
    procedure Button1Click(Sender: TObject);
    procedure DescriptionBoxChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure MenuItem4Click(Sender: TObject);
    procedure WordListClick(Sender: TObject);
    procedure WordListSelectionChange(Sender: TObject; User: boolean);
  private

  public
    selection : Integer;
    names : array of string; // index correlates with descriptions
    descriptions : array of string;

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
begin
  Form2.word_Name := 'Title';    // reset the variables on Form2
  Form2.Edit1.Text := 'Title';
  Form2.word_Desc := 'Description';
  Form2.Edit2.Text := 'Description';
  Form2.ShowModal; // show modal pauses execution until the other form has been closed

  if not Form2.cancelled then
  begin
    Form1.WordList.Items.Add(Form2.word_Name);
    setLength(names, WordList.Items.Count);
    names[WordList.Items.Count - 1] := Form2.word_Name;
    setLength(descriptions, WordList.Items.Count);
    descriptions[WordList.Items.Count - 1] := Form2.word_Desc;
  end;

end;

procedure TForm1.DescriptionBoxChange(Sender: TObject);
begin
  descriptions[selection]:= DescriptionBox.Text; // update description from Desc box
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  selection := 0; // initialize variables
  setLength(names, 0);
  setLength(descriptions, 0);
end;

procedure TForm1.MenuItem4Click(Sender: TObject);
begin
  // save procedure

end;

procedure TForm1.WordListClick(Sender: TObject);
begin

end;

procedure TForm1.WordListSelectionChange(Sender: TObject; User: boolean);
begin
  selection := WordList.ItemIndex;
  DescriptionBox.Text:=descriptions[selection];
  TestLabel.Caption:=selection.ToString;
end;

end.

