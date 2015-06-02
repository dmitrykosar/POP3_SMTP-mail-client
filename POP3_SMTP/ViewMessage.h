#pragma once
#include "classes.h"
#include <stdio.h>
#include "NewMail.h"
#include <tchar.h>

namespace POP3_SMTP {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Сводка для ViewMessage
	/// </summary>
	public ref class ViewMessage : public System::Windows::Forms::Form
	{
	public:
		eMail *temp;
	private: System::Windows::Forms::ListView^  listView1;
	public:
		Client *client;
		ViewMessage(void)
		{

			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

		ViewMessage(Client *client)
		{
			this->client = client;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ViewMessage()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  письмоToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  переслатьToolStripMenuItem;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->письмоToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->переслатьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"От: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 60);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(36, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Кому:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 86);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Тема: ";
			this->label3->Click += gcnew System::EventHandler(this, &ViewMessage::label3_Click);
			// 
			// webBrowser1
			// 
			this->webBrowser1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->webBrowser1->Location = System::Drawing::Point(12, 109);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(715, 278);
			this->webBrowser1->TabIndex = 3;
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(61, 31);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(577, 20);
			this->textBox1->TabIndex = 4;
			this->textBox1->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(61, 57);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(577, 20);
			this->textBox2->TabIndex = 5;
			// 
			// textBox3
			// 
			this->textBox3->Enabled = false;
			this->textBox3->Location = System::Drawing::Point(61, 83);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(577, 20);
			this->textBox3->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 412);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(129, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Прикрепленные файлы:";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->письмоToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(739, 24);
			this->menuStrip1->TabIndex = 8;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// письмоToolStripMenuItem
			// 
			this->письмоToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->переслатьToolStripMenuItem });
			this->письмоToolStripMenuItem->Name = L"письмоToolStripMenuItem";
			this->письмоToolStripMenuItem->Size = System::Drawing::Size(63, 20);
			this->письмоToolStripMenuItem->Text = L"Письмо";
			// 
			// переслатьToolStripMenuItem
			// 
			this->переслатьToolStripMenuItem->Name = L"переслатьToolStripMenuItem";
			this->переслатьToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->переслатьToolStripMenuItem->Text = L"Переслать";
			this->переслатьToolStripMenuItem->Click += gcnew System::EventHandler(this, &ViewMessage::переслатьToolStripMenuItem_Click);
			// 
			// listView1
			// 
			this->listView1->Location = System::Drawing::Point(12, 428);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(715, 79);
			this->listView1->TabIndex = 9;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &ViewMessage::listView1_SelectedIndexChanged);
			this->listView1->DoubleClick += gcnew System::EventHandler(this, &ViewMessage::listView1_DoubleClick);
			// 
			// ViewMessage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(739, 533);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->webBrowser1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"ViewMessage";
			this->Text = L"Просмотр письма";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void listView1_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
				 setlocale(LC_ALL, "Russian");
				 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
				 if (items->Count == 0)
					 return;
				 ListViewItem ^item = items[0];
				 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Regular);
				 int selectedItem = (int)item->Tag;
				 wchar_t * buf = new wchar_t[strlen(temp->attachments[selectedItem].path) + 1]();
				 size_t convertedChars = 0;
				// CharToOem(buf, temp->attachments[selectedItem].path);
				 mbstowcs_s(&convertedChars, buf, strlen(temp->attachments[selectedItem].path) + 1, temp->attachments[selectedItem].path, _TRUNCATE);
				 String ^str = gcnew System::String(temp->attachments[selectedItem].path);
				 int len = strlen(temp->attachments[selectedItem].path);
			//	 for (int j = 0; j < len ; j++)
				// {
					// buf[j] = temp->attachments[selectedItem].path[j];
				 //}
				 ShellExecute(0, L"open", buf, NULL, 0, SW_SHOW);
				 //WinExec((LPCSTR)buf, NULL);
	}
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
			 public: void View(eMail e)
			 {
						 temp = new eMail();
						 strcpy_s(temp->from, 50, client->MailBoxList[client->CurMailBox].User);
						 strcpy_s(temp->to, 250, e.to);
						 strcpy_s(temp->subject, 100, e.subject);
						 temp->body = (char*)calloc(sizeof(char)*(strlen(e.body) + 1), sizeof(char));
						 strcpy_s(temp->body, sizeof(char)*(strlen(e.body)+1),e.body );
						  this->textBox1->Text = gcnew System::String(e.from);
						  this->textBox2->Text = gcnew System::String(e.to);
						  this->textBox3->Text = gcnew System::String(e.subject);
						  
						  this->webBrowser1->DocumentText =   gcnew System::String(e.body);


						  array< System::Windows::Forms::LinkLabel^>  ^l;


						  for (int i = 0; i < e.attachments.size(); i++)
						  {
							
							  ListViewItem ^item = gcnew ListViewItem(gcnew System::String(e.attachments[i].name));
							  item->Tag = i;
							  listView1->Items->Add(item);
							  temp->attachments.push_back(e.attachments[i]);
						  }

						  /*
						  for (int i = 0; i < client->MailBoxList[client->CurMailBox].inbox.size(); i++)
						  {
							  String ^temps = gcnew System::String(client->MailBoxList[client->CurMailBox].inbox[i].from);
							  ListViewItem ^item = gcnew ListViewItem(temps);
							  item->Tag = i;
							  item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].inbox[i].subject));
							  item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].inbox[i].date));
							  if (client->MailBoxList[client->CurMailBox].inbox[i].r == false)
								  item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Bold);

							  listView1->Items->Add(item);
						  }



						  
						  for (int i = 0; i < e.attachments.size(); i++)
						  {
							  temp->attachments.push_back(e.attachments[i]);
							  System::Windows::Forms::LinkLabel^  tmp = gcnew System::Windows::Forms::LinkLabel();
							  tmp->AutoSize = true;
							  tmp->Text = gcnew String(e.attachments[i].name);
							  tmp->Location = System::Drawing::Point(20, 100+(i+1)*15);
							  tmp->Name = gcnew String(e.attachments[i].path);
							  tmp->TabIndex = 7;
							  tmp->Tag = i;
							  tmp->Click +=gcnew System::EventHandler(this, &POP3_SMTP::ViewMessage::OnClick);
							  this->Controls->Add(tmp);
							  this->Refresh();
							  this->Update();
						  }*/
			 }
					 private: System::Void OnClick(System::Object^  sender, System::EventArgs^  e)
					 {
								//  ShellExecuteEx((String^)((LinkLabel^)sender)->Name);
						//		  OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
							//		  openFileDialog1->FileName = (String^)((LinkLabel^)sender)->Name;
							//		  openFileDialog1->OpenFile();
									//  ShellExecute((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi((String^)((LinkLabel^)sender)->Name), (LPCWSTR)"", (LPCWSTR)"", (LPCWSTR)"open", (LPCWSTR)"");
									// Application::Run((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi((String^)((LinkLabel^)sender)->Name),"","","");
					 }
	private: System::Void переслатьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				 System::Threading::Thread^  a = gcnew Thread(gcnew ThreadStart(this, &ViewMessage::SendNewMail));
				 a->SetApartmentState(ApartmentState::STA);
				 a->Start();

	}
private: void SendNewMail()
{
			
			 
			 
			 NewMail ^nm = gcnew NewMail(temp);
			 nm->ShowDialog();
}
private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
