#include "classes.h"
#include <iostream>
#include <stdio.h>

#pragma once
 
namespace POP3_SMTP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для AddMailBox
	/// </summary>
	public ref class AddMailBox : public System::Windows::Forms::Form
	{
		Client *client;
	public:
		//Client *client;
		AddMailBox(Client *tmp)
		{
			client = tmp;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			
		}
	
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~AddMailBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::CheckBox^  checkBox1;

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Window;
			this->panel1->Controls->Add(this->checkBox1);
			this->panel1->Controls->Add(this->textBox5);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(703, 396);
			this->panel1->TabIndex = 0;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(50, 265);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(620, 20);
			this->textBox5->TabIndex = 9;
			this->textBox5->Text = L"smtp.mail.ru";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->CausesValidation = false;
			this->label5->Location = System::Drawing::Point(47, 245);
			this->label5->Margin = System::Windows::Forms::Padding(0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(139, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Сервер исходящей почты:";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(50, 210);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(620, 20);
			this->textBox4->TabIndex = 7;
			this->textBox4->Text = L"pop3.mail.ru";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->CausesValidation = false;
			this->label4->Location = System::Drawing::Point(47, 190);
			this->label4->Margin = System::Windows::Forms::Padding(0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(133, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Сервер входящей почты:";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(50, 155);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(620, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->Text = L"a4techgenius";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(47, 135);
			this->label3->Margin = System::Windows::Forms::Padding(0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(48, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Пароль:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(50, 100);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(620, 20);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = L"john.curt@mail.ru";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(47, 80);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Адрес E-mail:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(50, 45);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(620, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"John";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Ваше имя:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(412, 435);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(140, 25);
			this->button1->TabIndex = 1;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AddMailBox::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(575, 435);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(140, 25);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Отмена";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &AddMailBox::button2_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(50, 314);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(164, 17);
			this->checkBox1->TabIndex = 10;
			this->checkBox1->Text = L"Удалять письма с сервера";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// AddMailBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(727, 481);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Name = L"AddMailBox";
			this->Text = L"Cоздание нового почтового ящика";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
				 if (this->textBox1->Text == "" || this->textBox2->Text == "" || this->textBox3->Text == "")
				 {
					 MessageBox::Show("Заполните все поля");
					 return;
				 }
					
				 MailBox m((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox1->Text),
					 (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox2->Text),
					 (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox3->Text),
					 (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox4->Text),
					 (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox5->Text));
			
				 client->MailBoxList.push_back(m);

				 this->Close();
				

	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
}
};
}
