unit Unit2;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls;

type

  { TForm2 }

  TForm2 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Edit1Change(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
  private

  public
    const word_Name: string = '';
    const word_Desc: string = '';
    const cancelled: Boolean = false;
  end;

var
  Form2: TForm2;

implementation

{$R *.lfm}

{ TForm2 }

procedure TForm2.Button1Click(Sender: TObject);
begin      
  cancelled := false;
  Close;
end;

procedure TForm2.Button2Click(Sender: TObject);
begin
  cancelled := true;
  Close;
end;

procedure TForm2.Edit1Change(Sender: TObject);
begin
  word_Name := Edit1.Text;
end;

procedure TForm2.Edit2Change(Sender: TObject);
begin
  word_Desc := Edit2.Text;
end;

end.

