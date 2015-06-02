#include "classes.h"
#pragma once

namespace POP3_SMTP {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для NewMail
	/// </summary>
	public ref class NewMail : public System::Windows::Forms::Form
	{
	public:
		Client *client;
		
		NewMail(void)
		{
			
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		NewMail(Client *client)
		{
			this->client = client;

			InitializeComponent();
			this->textBox4->Text = gcnew System::String(client->MailBoxList[client->CurMailBox].User);
		}
		NewMail(eMail *e)
		{
			InitializeComponent();
			this->textBox4->Text = gcnew System::String(e->from);
			this->textBox1->Text = gcnew System::String(e->to);
			this->textBox2->Text = gcnew System::String(e->subject);
			this->richTextBox1->Text = gcnew  System::String(e->body);
			for (int i = 0; i < e->attachments.size(); i++)
			{
				
				System::Windows::Forms::LinkLabel^  tmp = gcnew System::Windows::Forms::LinkLabel();
				tmp->AutoSize = true;
				tmp->Text = gcnew String(e->attachments[i].name);
				tmp->Location = System::Drawing::Point(20, 100 + (i + 1) * 15);
				tmp->Name = gcnew String(e->attachments[i].path);
				tmp->TabIndex = 7;
				tmp->Tag = i;
//				tmp->Click += gcnew System::EventHandler(this, &POP3_SMTP::ViewMessage::OnClick);
				this->Controls->Add(tmp);
				this->Refresh();
				this->Update();
			}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~NewMail()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label4;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(36, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Кому:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 67);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(37, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Тема:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(55, 38);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(522, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"john_curt@mail.ru";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(55, 64);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(522, 20);
			this->textBox2->TabIndex = 3;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(16, 98);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(564, 270);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &NewMail::openFileDialog1_FileOk);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(233, 422);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(122, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Прекрепить файлы";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &NewMail::button1_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(16, 424);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(211, 20);
			this->textBox3->TabIndex = 6;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(471, 401);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(109, 44);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Отправить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &NewMail::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"От: ";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(55, 13);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(522, 20);
			this->textBox4->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(16, 408);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(129, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Прикрепленные файлы:";
			// 
			// NewMail
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(592, 453);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"NewMail";
			this->Text = L"Новое письмо";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 openFileDialog1->ShowDialog();
				
	}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 textBox3->Text = textBox3->Text + openFileDialog1->FileName+",";
			
		
			 
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			 eMail em;
			 array<String^>^ str;

			 str =textBox3->Text->Split( ',');

			 strcpy_s(em.from,50, (char*)client->MailBoxList[client->CurMailBox].User);
			 strcpy_s(em.to, 250, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textBox1->Text));
			 strcpy_s(em.subject ,100, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textBox2->Text));
			 strcpy_s(em.body ,500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(richTextBox1->Text));
			 System::DateTime d = System::DateTime::Now;
			 System::Globalization::CultureInfo ^cur = gcnew
				 System::Globalization::CultureInfo("en-US");
			strcpy_s(em.date ,50, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(d.ToString("yyyyMMddHHmmss", cur)));
			if (str->Length>0)
			for (int i = 0; i < str->Length-1; i++)
			{
				em.attachments.push_back(attachment((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str[i]), (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str[i])));
			}
			bool res = client->MailBoxList[client->CurMailBox].SendeMail(em);
			if (res)
				MessageBox::Show("Письмо не отправленно");

			this->Close();
}
};
}
