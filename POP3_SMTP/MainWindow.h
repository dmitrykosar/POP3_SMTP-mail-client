
#include <iostream>
#include "AddMailBox.h"
#include "DownloadForm.h"
#include "classes.h"
#include <vector>
#include <stdio.h>
#include <process.h>
#include "ViewMessage.h"
#include "NewMail.h"
#include "Loading.h"

using namespace std;
void AddMBox(Client *client);


#pragma once

namespace POP3_SMTP {
	
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	
	/// <summary>
	/// Ñâîäêà äëÿ MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	
	public:
		int selectedItem, selectedMailBox, selectedFolder;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	public:
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::ToolStripMenuItem^  ïèñüìîToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  íîâîåÏèñüìîToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ïåğåñëàòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  óäàëèòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ïîìåòèòüÊàêÑïàìToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton4;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
			 	Client *client;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
			 SearchResult *result;
	public:
		MainWindow(void)
		{
			client = new Client();
			Loading ^ld = gcnew Loading();
			ld->Show();
			client->LoadMailboxes();
			ld->Close();
		
			InitializeComponent();
			
			RefreshTreeView();
			this->FormClosed +=gcnew System::Windows::Forms::FormClosedEventHandler(this, &POP3_SMTP::MainWindow::Exit);

			//
			//TODO: äîáàâüòå êîä êîíñòğóêòîğà
			//
		
		}

	

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ğåñóğñû.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	public: delegate void Callback();
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	protected:
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ÿùèêToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ñîçäàòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ListView^  listView1;

			 ///
		///TreeView 
		///
		// vector<System::Windows::Forms::TreeView, allocator < System::Windows::Forms::TreeView > > MailBoxTree;
	private:
		/// <summary>
		/// Òğåáóåòñÿ ïåğåìåííàÿ êîíñòğóêòîğà.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Îáÿçàòåëüíûé ìåòîä äëÿ ïîääåğæêè êîíñòğóêòîğà - íå èçìåíÿéòå
		/// ñîäåğæèìîå äàííîãî ìåòîäà ïğè ïîìîùè ğåäàêòîğà êîäà.
		/// </summary>
	void InitializeComponent(void)
		{
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
		this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
		this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->ÿùèêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->ñîçäàòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->ïèñüìîToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->íîâîåÏèñüìîToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->ïåğåñëàòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->óäàëèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->ïîìåòèòüÊàêÑïàìToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->treeView1 = (gcnew System::Windows::Forms::TreeView());
		this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
		this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
		this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
		this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
		this->listView1 = (gcnew System::Windows::Forms::ListView());
		this->statusStrip1->SuspendLayout();
		this->menuStrip1->SuspendLayout();
		this->toolStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// statusStrip1
		// 
		this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->toolStripStatusLabel1,
				this->toolStripStatusLabel2
		});
		this->statusStrip1->Location = System::Drawing::Point(0, 422);
		this->statusStrip1->Name = L"statusStrip1";
		this->statusStrip1->Size = System::Drawing::Size(1066, 22);
		this->statusStrip1->TabIndex = 0;
		this->statusStrip1->Text = L"statusStrip1";
		// 
		// toolStripStatusLabel1
		// 
		this->toolStripStatusLabel1->BackColor = System::Drawing::SystemColors::ButtonFace;
		this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
		this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
		// 
		// toolStripStatusLabel2
		// 
		this->toolStripStatusLabel2->BackColor = System::Drawing::SystemColors::Menu;
		this->toolStripStatusLabel2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
		this->toolStripStatusLabel2->Size = System::Drawing::Size(118, 17);
		this->toolStripStatusLabel2->Text = L"toolStripStatusLabel2";
		// 
		// menuStrip1
		// 
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->ÿùèêToolStripMenuItem,
				this->ïèñüìîToolStripMenuItem
		});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1066, 24);
		this->menuStrip1->TabIndex = 1;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// ÿùèêToolStripMenuItem
		// 
		this->ÿùèêToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->ñîçäàòüToolStripMenuItem,
				this->óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem
		});
		this->ÿùèêToolStripMenuItem->Name = L"ÿùèêToolStripMenuItem";
		this->ÿùèêToolStripMenuItem->Size = System::Drawing::Size(50, 20);
		this->ÿùèêToolStripMenuItem->Text = L"ßùèê";
		// 
		// ñîçäàòüToolStripMenuItem
		// 
		this->ñîçäàòüToolStripMenuItem->Name = L"ñîçäàòüToolStripMenuItem";
		this->ñîçäàòüToolStripMenuItem->Size = System::Drawing::Size(209, 22);
		this->ñîçäàòüToolStripMenuItem->Text = L"Íîâûé ïî÷òîâûé ÿùèê";
		this->ñîçäàòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::ñîçäàòüToolStripMenuItem_Click);
		// 
		// óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem
		// 
		this->óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem->Name = L"óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem";
		this->óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem->Size = System::Drawing::Size(209, 22);
		this->óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem->Text = L"Óäàëèòü ïî÷òîâûé ÿùèê";
		this->óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem_Click);
		// 
		// ïèñüìîToolStripMenuItem
		// 
		this->ïèñüìîToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
			this->íîâîåÏèñüìîToolStripMenuItem,
				this->ïåğåñëàòüToolStripMenuItem, this->óäàëèòüToolStripMenuItem, this->ïîìåòèòüÊàêÑïàìToolStripMenuItem, this->ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem
		});
		this->ïèñüìîToolStripMenuItem->Name = L"ïèñüìîToolStripMenuItem";
		this->ïèñüìîToolStripMenuItem->Size = System::Drawing::Size(63, 20);
		this->ïèñüìîToolStripMenuItem->Text = L"Ïèñüìî";
		// 
		// íîâîåÏèñüìîToolStripMenuItem
		// 
		this->íîâîåÏèñüìîToolStripMenuItem->Name = L"íîâîåÏèñüìîToolStripMenuItem";
		this->íîâîåÏèñüìîToolStripMenuItem->Size = System::Drawing::Size(225, 22);
		this->íîâîåÏèñüìîToolStripMenuItem->Text = L"Íîâîå ïèñüìî";
		this->íîâîåÏèñüìîToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::íîâîåÏèñüìîToolStripMenuItem_Click);
		// 
		// ïåğåñëàòüToolStripMenuItem
		// 
		this->ïåğåñëàòüToolStripMenuItem->Name = L"ïåğåñëàòüToolStripMenuItem";
		this->ïåğåñëàòüToolStripMenuItem->Size = System::Drawing::Size(225, 22);
		this->ïåğåñëàòüToolStripMenuItem->Text = L"Ïåğåñëàòü";
		this->ïåğåñëàòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::ïåğåñëàòüToolStripMenuItem_Click);
		// 
		// óäàëèòüToolStripMenuItem
		// 
		this->óäàëèòüToolStripMenuItem->Name = L"óäàëèòüToolStripMenuItem";
		this->óäàëèòüToolStripMenuItem->Size = System::Drawing::Size(225, 22);
		this->óäàëèòüToolStripMenuItem->Text = L"Óäàëèòü";
		this->óäàëèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::óäàëèòüToolStripMenuItem_Click);
		// 
		// ïîìåòèòüÊàêÑïàìToolStripMenuItem
		// 
		this->ïîìåòèòüÊàêÑïàìToolStripMenuItem->Name = L"ïîìåòèòüÊàêÑïàìToolStripMenuItem";
		this->ïîìåòèòüÊàêÑïàìToolStripMenuItem->Size = System::Drawing::Size(225, 22);
		this->ïîìåòèòüÊàêÑïàìToolStripMenuItem->Text = L"Ïîìåòèòü êàê ñïàì";
		this->ïîìåòèòüÊàêÑïàìToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::ïîìåòèòüÊàêÑïàìToolStripMenuItem_Click);
		// 
		// ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem
		// 
		this->ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem->Name = L"ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem";
		this->ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem->Size = System::Drawing::Size(225, 22);
		this->ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem->Text = L"Ïîìåòèòü êàê ïğî÷èòàííîå";
		this->ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem_Click);
		// 
		// treeView1
		// 
		this->treeView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left));
		this->treeView1->Location = System::Drawing::Point(0, 72);
		this->treeView1->Name = L"treeView1";
		this->treeView1->Size = System::Drawing::Size(194, 347);
		this->treeView1->TabIndex = 2;
		this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainWindow::treeView1_AfterSelect);
		// 
		// toolStrip1
		// 
		this->toolStrip1->AutoSize = false;
		this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
			this->toolStripButton1,
				this->toolStripButton3, this->toolStripSeparator2, this->toolStripButton4, this->toolStripSeparator1, this->toolStripLabel1,
				this->toolStripTextBox1, this->toolStripButton2, this->toolStripButton5
		});
		this->toolStrip1->Location = System::Drawing::Point(0, 24);
		this->toolStrip1->Name = L"toolStrip1";
		this->toolStrip1->Size = System::Drawing::Size(1066, 45);
		this->toolStrip1->TabIndex = 3;
		this->toolStrip1->Text = L"toolStrip1";
		this->toolStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MainWindow::toolStrip1_ItemClicked);
		// 
		// toolStripButton1
		// 
		this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
		this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
		this->toolStripButton1->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
		this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton1->Name = L"toolStripButton1";
		this->toolStripButton1->Size = System::Drawing::Size(37, 42);
		this->toolStripButton1->Text = L"Çàãğóçèòü ïèñüìà";
		this->toolStripButton1->Click += gcnew System::EventHandler(this, &MainWindow::toolStripButton1_Click);
		// 
		// toolStripButton3
		// 
		this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
		this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton3.Image")));
		this->toolStripButton3->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
		this->toolStripButton3->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
		this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton3->Name = L"toolStripButton3";
		this->toolStripButton3->Size = System::Drawing::Size(37, 42);
		this->toolStripButton3->Text = L"Íîâîå ïèñüìî";
		this->toolStripButton3->Click += gcnew System::EventHandler(this, &MainWindow::toolStripButton3_Click);
		// 
		// toolStripSeparator2
		// 
		this->toolStripSeparator2->Name = L"toolStripSeparator2";
		this->toolStripSeparator2->Size = System::Drawing::Size(6, 45);
		// 
		// toolStripButton4
		// 
		this->toolStripButton4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
		this->toolStripButton4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton4.Image")));
		this->toolStripButton4->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
		this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton4->Name = L"toolStripButton4";
		this->toolStripButton4->Size = System::Drawing::Size(37, 42);
		this->toolStripButton4->Text = L"toolStripButton4";
		this->toolStripButton4->Click += gcnew System::EventHandler(this, &MainWindow::toolStripButton4_Click);
		// 
		// toolStripSeparator1
		// 
		this->toolStripSeparator1->Name = L"toolStripSeparator1";
		this->toolStripSeparator1->Size = System::Drawing::Size(6, 45);
		// 
		// toolStripLabel1
		// 
		this->toolStripLabel1->Name = L"toolStripLabel1";
		this->toolStripLabel1->Size = System::Drawing::Size(45, 42);
		this->toolStripLabel1->Text = L"Ïîèñê:";
		// 
		// toolStripTextBox1
		// 
		this->toolStripTextBox1->Name = L"toolStripTextBox1";
		this->toolStripTextBox1->Size = System::Drawing::Size(100, 45);
		// 
		// toolStripButton2
		// 
		this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
		this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton2.Image")));
		this->toolStripButton2->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
		this->toolStripButton2->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
		this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton2->Name = L"toolStripButton2";
		this->toolStripButton2->Size = System::Drawing::Size(37, 42);
		this->toolStripButton2->Text = L"Ïîèñê";
		this->toolStripButton2->Click += gcnew System::EventHandler(this, &MainWindow::toolStripButton2_Click);
		// 
		// toolStripButton5
		// 
		this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
		this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton5.Image")));
		this->toolStripButton5->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
		this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->toolStripButton5->Name = L"toolStripButton5";
		this->toolStripButton5->Size = System::Drawing::Size(38, 42);
		this->toolStripButton5->Text = L"Ïîìåòèòü êàê ñïàì";
		this->toolStripButton5->Click += gcnew System::EventHandler(this, &MainWindow::toolStripButton5_Click);
		// 
		// listView1
		// 
		this->listView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->listView1->Location = System::Drawing::Point(193, 72);
		this->listView1->Name = L"listView1";
		this->listView1->Size = System::Drawing::Size(861, 347);
		this->listView1->TabIndex = 4;
		this->listView1->UseCompatibleStateImageBehavior = false;
		this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::listView1_SelectedIndexChanged);
		this->listView1->DoubleClick += gcnew System::EventHandler(this, &MainWindow::listView1_DoubleClick);
		// 
		// MainWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::Color::Cornsilk;
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		this->ClientSize = System::Drawing::Size(1066, 444);
		this->Controls->Add(this->listView1);
		this->Controls->Add(this->toolStrip1);
		this->Controls->Add(this->treeView1);
		this->Controls->Add(this->statusStrip1);
		this->Controls->Add(this->menuStrip1);
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"MainWindow";
		this->RightToLeft = System::Windows::Forms::RightToLeft::No;
		this->Text = L"Ïî÷òîâûé êëèåíò ";
		this->statusStrip1->ResumeLayout(false);
		this->statusStrip1->PerformLayout();
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		this->toolStrip1->ResumeLayout(false);
		this->toolStrip1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion
private: System::Void Exit(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e){
					 client->SaveClientStatus();
					 client->SaveMailboxes();
		}
private: System::Void ñîçäàòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				 
				 POP3_SMTP::AddMailBox ^AddForm = gcnew POP3_SMTP::AddMailBox(client);
				 AddForm->Show();
				
			//	 WaitForSingleObject(hMutex, INFINITE);
				 AddForm->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &POP3_SMTP::MainWindow::AddMailBox_toTree);
				
				 
				 
	}
private: System::Void AddMailBox_toTree(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
	{

				 MessageBox::Show("Added!!!");
				 RefreshTreeView();
				 /*
				 System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"Âõîäÿùèå"));

				 System::Windows::Forms::TreeNode^  treeNode = (gcnew System::Windows::Forms::TreeNode(L"Óçåë0", gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode1 }));
				
					 
					 treeNode1->Name = L"inbox";
					 treeNode1->Text = L"Âõîäÿùèå";
					 treeNode->Name = client->MailBoxList[0].MailBoxName;
					 treeNode->Text = client->MailBoxList[0].MailBoxName;
					 this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode });
				*/
				
					
	}	
private: System::Void óäàëèòüÏî÷òîâûéßùèêToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				   if (client->MailBoxList.size())
				   if (treeView1->Focused)
			 {

				 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
				 int i = ((Ftype^)treeNode1->Tag)->MailboxNum;
				 client->MailBoxList.erase((client->MailBoxList.begin() + i));
				 RefreshTreeView();
			 }
			 else
			 {
				 MessageBox::Show("Âûáåğèòå ïî÷òîâûé ÿùèê");
			 }
}
private: void RefreshTreeView()
{
			 treeView1->Nodes->Clear();
			 for (int i = 0; i < client->MailBoxList.size(); i++)
			 {
				 Ftype^ t = gcnew Ftype();
				 System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"Inbox"));
				 System::Windows::Forms::TreeNode^  treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"Outbox"));
				 System::Windows::Forms::TreeNode^  treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"Spam"));
				 System::Windows::Forms::TreeNode^  treeNode4 = (gcnew System::Windows::Forms::TreeNode(L"Trash"));
				 System::Windows::Forms::TreeNode^  treeNode5 = (gcnew System::Windows::Forms::TreeNode(gcnew System::String(client->MailBoxList[i].MailBoxName), gcnew cli::array< System::Windows::Forms::TreeNode^  >(4) {
					 treeNode1, treeNode2, treeNode3, treeNode4
				 }));
				 //	 this->SuspendLayout();
				 t->MailboxNum = i;
				 t->type = 0;
				 treeNode1->Name = L"Inbox";
				 treeNode1->Text = L"Âõîäÿùèå";
				 treeNode1->Tag = t;
				 treeNode2->Name = L"Outbox";
				 treeNode2->Text = L"Îòïğàâëåííûå";
				 t->type = 1;
				 treeNode2->Tag = t;
				 treeNode3->Name = L"Spam";
				 treeNode3->Text = L"Ñïàì";
				 t->type = 2;
				 treeNode3->Tag = t;
				 treeNode4->Name = L"Trash";
				 treeNode4->Text = L"Êîğçèíà";
				 t->type = 3;
				 treeNode4->Tag = t;
				 t->type = 4;
				 treeNode5->Tag = t;
				 this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode5 });
				 this->treeView1->TabIndex = 0;
				 treeView1->AfterSelect +=gcnew System::Windows::Forms::TreeViewEventHandler(this, &POP3_SMTP::MainWindow::OnAfterSelect);
			 }
}
private: System::Void OnAfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
		 {
					  System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
					  treeNode1 = treeView1->SelectedNode;
					  treeNode1 = treeView1->SelectedNode;
					  Ftype^ t = gcnew Ftype();
					  t = (Ftype^)treeNode1->Tag;
					  client->CurMailBox = t->MailboxNum;
					  if (treeNode1->Name == "Inbox")
					  {
						  ShowInbox();
					  }
					  if (treeNode1->Name == "Outbox")
					  {
						  ShowOutBox();
						 
					  }
					  if (treeNode1->Name == "Spam")
					  {
						  ShowSpam();
					  }
					  if (treeNode1->Name == "Trash")
					  {
						  ShowTrash();
					  }
					 

		 }
private: void ShowSpam()
			   {
							
								listView1->Clear();
								listView1->View = System::Windows::Forms::View::Details;
								listView1->MultiSelect = true;
								listView1->HideSelection = false;
								listView1->HeaderStyle = ColumnHeaderStyle::Nonclickable;
								ColumnHeader^ columnHeader1 = gcnew ColumnHeader;
								columnHeader1->Text = "Îò";
								columnHeader1->TextAlign = HorizontalAlignment::Left;
								columnHeader1->Width = 300;
								ColumnHeader^ columnHeader2 = gcnew ColumnHeader;
								columnHeader2->Text = "Òåìà";
								columnHeader2->TextAlign = HorizontalAlignment::Center;
								columnHeader2->Width = 300;
								ColumnHeader^ columnHeader3 = gcnew ColumnHeader;
								columnHeader3->Text = "Äàòà";
								columnHeader3->TextAlign = HorizontalAlignment::Center;
								columnHeader3->Width = 100;
								listView1->Columns->Add(columnHeader1);
								listView1->Columns->Add(columnHeader2);
								listView1->Columns->Add(columnHeader3);





								for (int i = 0; i < client->MailBoxList[client->CurMailBox].spam.size(); i++)
								{
									String ^temps = gcnew System::String(client->MailBoxList[client->CurMailBox].spam[i].from);
									ListViewItem ^item = gcnew ListViewItem(temps);
									item->Tag = i;
									item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].spam[i].subject));
									item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].spam[i].date));
									if (client->MailBoxList[client->CurMailBox].spam[i].r == false)
										item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Bold);

									listView1->Items->Add(item);
								}
							
			   }
private: void ShowTrash()
{
			 listView1->Clear();
			 listView1->View = System::Windows::Forms::View::Details;
			 listView1->MultiSelect = true;
			 listView1->HideSelection = false;
			 listView1->HeaderStyle = ColumnHeaderStyle::Nonclickable;
			 ColumnHeader^ columnHeader1 = gcnew ColumnHeader;
			 columnHeader1->Text = "Îò";
			 columnHeader1->TextAlign = HorizontalAlignment::Left;
			 columnHeader1->Width = 300;
			 ColumnHeader^ columnHeader2 = gcnew ColumnHeader;
			 columnHeader2->Text = "Òåìà";
			 columnHeader2->TextAlign = HorizontalAlignment::Center;
			 columnHeader2->Width = 300;
			 ColumnHeader^ columnHeader3 = gcnew ColumnHeader;
			 columnHeader3->Text = "Äàòà";
			 columnHeader3->TextAlign = HorizontalAlignment::Center;
			 columnHeader3->Width = 100;
			 listView1->Columns->Add(columnHeader1);
			 listView1->Columns->Add(columnHeader2);
			 listView1->Columns->Add(columnHeader3);





			 for (int i = 0; i < client->MailBoxList[client->CurMailBox].trash.size(); i++)
			 {
				 String ^temps = gcnew System::String(client->MailBoxList[client->CurMailBox].trash[i].from);
				 ListViewItem ^item = gcnew ListViewItem(temps);
				 item->Tag = i;
				 item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].trash[i].subject));
				 item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].trash[i].date));
				 if (client->MailBoxList[client->CurMailBox].trash[i].r == false)
					 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Bold);

				 listView1->Items->Add(item);
			 }
}
private: void ShowOutBox()
			   {
							OutputStyle();
							for (int i = 0; i < client->MailBoxList[client->CurMailBox].outbox.size(); i++)
							{
								String ^temps = gcnew System::String(client->MailBoxList[client->CurMailBox].outbox[i].to);
								ListViewItem ^item = gcnew ListViewItem(temps);
								item->Tag = i;
								item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].outbox[i].subject));
								item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].outbox[i].date));
								if (client->MailBoxList[client->CurMailBox].outbox[i].r == false)
									item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Bold);

								listView1->Items->Add(item);
							}

			   }
private:  void InputStyle()
		{
					if (this->listView1->InvokeRequired)
					{
						Callback^ cd = gcnew Callback(this, &MainWindow::InputStyle);
						this->listView1->Invoke(cd);
					}
					else
					{

						listView1->Clear();
						listView1->View = System::Windows::Forms::View::Details;
						listView1->MultiSelect = true;
						listView1->HideSelection = false;
						listView1->HeaderStyle = ColumnHeaderStyle::Nonclickable;
						ColumnHeader^ columnHeader1 = gcnew ColumnHeader;
						columnHeader1->Text = "Îò";
						columnHeader1->TextAlign = HorizontalAlignment::Left;
						// columnHeader1->Width = 300;
						ColumnHeader^ columnHeader2 = gcnew ColumnHeader;
						columnHeader2->Text = "Òåìà";
						columnHeader2->TextAlign = HorizontalAlignment::Center;
						//	 columnHeader2->Width = 380;
						ColumnHeader^ columnHeader3 = gcnew ColumnHeader;
						columnHeader3->Text = "Äàòà";
						columnHeader3->TextAlign = HorizontalAlignment::Center;
						// columnHeader3->Width = 233;
						listView1->Columns->Add(columnHeader1);
						listView1->Columns->Add(columnHeader2);
						listView1->Columns->Add(columnHeader3);
					}
		}
private: void OutputStyle()
				 {
							  this->listView1->Clear();
							  this->listView1->View = System::Windows::Forms::View::Details;
							  this->listView1->MultiSelect = true;
							  this->listView1->HideSelection = false;
							  this->listView1->HeaderStyle = ColumnHeaderStyle::Nonclickable;
							  ColumnHeader^ columnHeader1 = gcnew ColumnHeader;
							  columnHeader1->Text = "Êîìó";
							  columnHeader1->TextAlign = HorizontalAlignment::Left;
							   columnHeader1->Width = 100;
							  ColumnHeader^ columnHeader2 = gcnew ColumnHeader;
							  columnHeader2->Text = "Òåìà";
							  columnHeader2->TextAlign = HorizontalAlignment::Center;
							  	 columnHeader2->Width = 100;
							  ColumnHeader^ columnHeader3 = gcnew ColumnHeader;
							  columnHeader3->Text = "Äàòà";
							  columnHeader3->TextAlign = HorizontalAlignment::Center;
							  // columnHeader3->Width = 233;
							  this->listView1->Columns->Add(columnHeader1);
							  this->listView1->Columns->Add(columnHeader2);
							  this->listView1->Columns->Add(columnHeader3);
				 }
private: void In_OutputStyle()
			 {
										this->listView1->Clear();
										this->listView1->View = System::Windows::Forms::View::Details;
										this->listView1->MultiSelect = true;
										this->listView1->HideSelection = false;
										this->listView1->HeaderStyle = ColumnHeaderStyle::Nonclickable;
										ColumnHeader^ columnHeader1 = gcnew ColumnHeader;
										columnHeader1->Text = "Êîìó";
										columnHeader1->TextAlign = HorizontalAlignment::Left;
										 columnHeader1->Width = 100;
										ColumnHeader^ columnHeader2 = gcnew ColumnHeader;
										columnHeader2->Text = "Òåìà";
										columnHeader2->TextAlign = HorizontalAlignment::Center;
											 columnHeader2->Width = 100;
										ColumnHeader^ columnHeader3 = gcnew ColumnHeader;
										columnHeader3->Text = "Äàòà";
										columnHeader3->TextAlign = HorizontalAlignment::Center;
										 columnHeader3->Width = 100;
										ColumnHeader^ columnHeader4 = gcnew ColumnHeader;
										columnHeader4->Text = "Îò";
										columnHeader4->TextAlign = HorizontalAlignment::Center;
										this->listView1->Columns->Add(columnHeader1);
										this->listView1->Columns->Add(columnHeader4);
										this->listView1->Columns->Add(columnHeader2);
										this->listView1->Columns->Add(columnHeader3);
										
						   }

private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 if (client->MailBoxList.size() > 0)
			 {
				 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
				 treeNode1 = treeView1->SelectedNode;
				 treeNode1 = treeView1->SelectedNode;
				 Ftype^ t = gcnew Ftype();
				 t = (Ftype^)treeNode1->Tag;
				 client->CurMailBox = t->MailboxNum;

				 System::Threading::Thread^  a = gcnew Thread(gcnew ThreadStart(this, &MainWindow::DownloadAndShow));

				 a->Start();
			 }
			 

}
private:  void DownloadAndShow()
{
			 
			int c =  client->MailBoxList[client->CurMailBox].DownloadAndSave();
			ShowInbox();
			
}
private:  void ShowInbox()
{	
			  if (this->listView1->InvokeRequired)
			  {
				  Callback^ cd = gcnew Callback(this, &MainWindow::ShowInbox);
				  this->listView1->Invoke(cd);
			  }
			  else
			  {
				  listView1->Clear();
				  listView1->View = System::Windows::Forms::View::Details;
				  listView1->MultiSelect = true;
				  listView1->HideSelection = false;
				  listView1->HeaderStyle = ColumnHeaderStyle::Nonclickable;
				  ColumnHeader^ columnHeader1 = gcnew ColumnHeader;
				  columnHeader1->Text = "Îò";
				  columnHeader1->TextAlign = HorizontalAlignment::Left;
				   columnHeader1->Width = 300;
				  ColumnHeader^ columnHeader2 = gcnew ColumnHeader;
				  columnHeader2->Text = "Òåìà";
				  columnHeader2->TextAlign = HorizontalAlignment::Center;
				  	 columnHeader2->Width = 300;
				  ColumnHeader^ columnHeader3 = gcnew ColumnHeader;
				  columnHeader3->Text = "Äàòà";
				  columnHeader3->TextAlign = HorizontalAlignment::Center;
				   columnHeader3->Width = 100;
				  listView1->Columns->Add(columnHeader1);
				  listView1->Columns->Add(columnHeader2);
				  listView1->Columns->Add(columnHeader3);


				  int h = client->MailBoxList[client->CurMailBox].inbox.size();
				  h = client->CurMailBox;


				  for (int i = 0; i < client->MailBoxList[client->CurMailBox].inbox.size(); i++)
				  {
					  String ^temps = gcnew System::String(client->MailBoxList[client->CurMailBox].inbox[i].from);
					  ListViewItem ^item = gcnew ListViewItem(temps);
					  item->Tag = i;
					  item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].inbox[i].subject));
					  item->SubItems->Add(gcnew System::String(client->MailBoxList[client->CurMailBox].inbox[i].date));
					  if (client->MailBoxList[client->CurMailBox].inbox[i].r==false)
						  item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Bold);
					  
					  listView1->Items->Add(item);
				  }
			  }
}
private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 
}
private: System::Void listView1_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			 
			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
				 return;


			 ListViewItem ^item = items[0];
			 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Regular);
			 selectedItem = (int)item->Tag;

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 if (selectedFolder != 5)
			 {

				 if (treeNode1->Name == "Inbox")
				 {

					 selectedFolder = 0;
					 if (client->MailBoxList[client->CurMailBox].inbox[selectedItem].r == false)
					 {

						 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Underline);
						 client->MailBoxList[client->CurMailBox].inbox[selectedItem].r = true;
					 }
				 }
				 if (treeNode1->Name == "Outbox")
					 selectedFolder = 1;
				 if (treeNode1->Name == "Spam")
				 {

					 selectedFolder = 2;
					 if (client->MailBoxList[client->CurMailBox].spam[selectedItem].r == false)
					 {

						 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Underline);
						 client->MailBoxList[client->CurMailBox].spam[selectedItem].r = true;
					 }
				 }
				 if (treeNode1->Name == "Trash")
					 selectedFolder = 3;

			 }
			 else
			 {
				 if (result->e[selectedItem].r == false)
				 {

					 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Underline);
					 result->e[selectedItem].r = true;
				 }
			 }

			 System::Threading::Thread^  a = gcnew Thread(gcnew ThreadStart(this, &MainWindow::ShowMessage));
			 a->SetApartmentState(ApartmentState::STA);
			
			 a->Start();
		
			
			
}
private: void ShowMessage()
	{
			 

			 ViewMessage ^v = gcnew ViewMessage(client);
			 
			 if (selectedFolder == 0)
			 v->View(client->MailBoxList[client->CurMailBox].inbox[selectedItem]);
			 if (selectedFolder == 1)
				 v->View(client->MailBoxList[client->CurMailBox].outbox[selectedItem]);

			 if (selectedFolder == 2)
				 v->View(client->MailBoxList[client->CurMailBox].spam[selectedItem]);

			 if (selectedFolder == 3)
				 v->View(client->MailBoxList[client->CurMailBox].trash[selectedItem]);
			 if (selectedFolder == 5)
			 {

				 v->View(result->e[selectedItem]);
				
			 }
			
			 v->ShowDialog();
			 v->Refresh();
			
	}
private: System::Void toolStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
}
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (client->MailBoxList.size() > 0)
			 {

				 System::Threading::Thread^  a = gcnew Thread(gcnew ThreadStart(this, &MainWindow::SendNewMail));
				 a->SetApartmentState(ApartmentState::STA);
				 a->Start();
			 }
}
private: void SendNewMail()
{
			 NewMail ^nm = gcnew NewMail(client);
			 nm->ShowDialog();
}
private: System::Void íîâîåÏèñüìîToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (client->MailBoxList.size())
			 {
				 System::Threading::Thread^  a = gcnew Thread(gcnew ThreadStart(this, &MainWindow::SendNewMail));
				 a->SetApartmentState(ApartmentState::STA);
				 a->Start();
			 }
}
private: System::Void ïåğåñëàòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
			 {
				 MessageBox::Show("Âûáåğèòå ïèñüìî");
				 return;
			 }

			 ListViewItem ^item = items[0];
			 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Regular);
			 selectedItem = (int)item->Tag;

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 if (treeNode1->Name == "Inbox")
				 selectedFolder = 0;
			 if (treeNode1->Name == "Outbox")
				 selectedFolder = 1;
			 if (treeNode1->Name == "Spam")
				 selectedFolder = 2;
			 if (treeNode1->Name == "Trash")
				 selectedFolder = 3;

			 System::Threading::Thread^  a = gcnew Thread(gcnew ThreadStart(this, &MainWindow::ShowMessage));
			 a->SetApartmentState(ApartmentState::STA);

			 a->Start();
}
private: System::Void ïîìåòèòüÊàêÏğî÷èòàííîåToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
			 {
				 MessageBox::Show("Âûáåğèòå ïèñüìî");
				 return;
			 }


			 ListViewItem ^item = items[0];
			 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Regular);
			 selectedItem = (int)item->Tag;

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 if (treeNode1->Name == "Inbox")
				 selectedFolder = 0;
			 if (treeNode1->Name == "Outbox")
				 selectedFolder = 1;
			 if (treeNode1->Name == "Spam")
				 selectedFolder = 2;
			 if (treeNode1->Name == "Trash")
				 selectedFolder = 3;



			

			 if (client->MailBoxList[client->CurMailBox].inbox[selectedItem].r == false)
				 item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Underline);

}
private: System::Void óäàëèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
			 {
				 MessageBox::Show("Âûáåğèòå ïèñüìî");
				 return;
			 }

			 ListViewItem ^item = items[0];
			
			 selectedItem = (int)item->Tag;

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 if (treeNode1->Name == "Inbox")
			 {
				 selectedFolder = 0;
				 client->MailBoxList[client->CurMailBox].AddToTrash(selectedFolder, selectedItem);
				 ShowInbox();
			 }
			 if (treeNode1->Name == "Outbox")
			 {
				 selectedFolder = 1;
				 client->MailBoxList[client->CurMailBox].AddToTrash(selectedFolder, selectedItem);
				 ShowOutBox();
			 }
			 if (treeNode1->Name == "Spam")
			 {

				 selectedFolder = 2;
				 client->MailBoxList[client->CurMailBox].AddToTrash(selectedFolder, selectedItem);
				 InputStyle();
			 }
			 if (treeNode1->Name == "Trash")
			 {
				 selectedFolder = 3;
				 client->MailBoxList[client->CurMailBox].DeleteMail(selectedItem);
				 In_OutputStyle();
			 }

}
private: System::Void ïîìåòèòüÊàêÑïàìToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
			 {
				 MessageBox::Show("Âûáåğèòå ïèñüìî");
				 return;
			 }

			 ListViewItem ^item = items[0];
			
			 selectedItem = (int)item->Tag;
			 if (treeNode1->Name == "Inbox")
			 {
				 selectedFolder = 0;
				 client->MailBoxList[client->CurMailBox].AddToSpam(selectedItem);
				 ShowInbox();

			 }


}
private: System::Void toolStripButton4_Click(System::Object^  sender, System::EventArgs^  e) {
			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
			 {
				 MessageBox::Show("Âûáåğèòå ïèñüìî");
				 return;
			 }

			 ListViewItem ^item = items[0];

			 selectedItem = (int)item->Tag;

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 if (treeNode1->Name == "Inbox")
			 {
				 selectedFolder = 0;
				 client->MailBoxList[client->CurMailBox].AddToTrash(selectedFolder, selectedItem);
				 ShowInbox();
			 }
			 if (treeNode1->Name == "Outbox")
			 {
				 selectedFolder = 1;
				 client->MailBoxList[client->CurMailBox].AddToTrash(selectedFolder, selectedItem);
				 ShowOutBox();
			 }
			 if (treeNode1->Name == "Spam")
			 {
				 selectedFolder = 2;
				 client->MailBoxList[client->CurMailBox].AddToTrash(selectedFolder, selectedItem);
				 InputStyle();
			 }
			 if (treeNode1->Name == "Trash")
			 {
				 selectedFolder = 3;
				 client->MailBoxList[client->CurMailBox].trash.erase(client->MailBoxList[client->CurMailBox].trash.begin() + selectedItem);
				 In_OutputStyle();
			 }
}
private: System::Void toolStripButton5_Click(System::Object^  sender, System::EventArgs^  e) {
			 ListView::SelectedListViewItemCollection^ items = this->listView1->SelectedItems;
			 if (items->Count == 0)
			 {
				 MessageBox::Show("Âûáåğèòå ïèñüìî");
				 return;
			 }

			 ListViewItem ^item = items[0];

			 selectedItem = (int)item->Tag;

			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;
			 if (treeNode1->Name == "Inbox")
			 {
				 selectedFolder = 0;
				 client->MailBoxList[client->CurMailBox].AddToSpam(selectedItem);
				 ShowInbox();
			 }
}
private: void ShowSearchResult()
		 {
					  In_OutputStyle();
					  for (int i = 0; i < result->e.size(); i++)
					  {
						  String ^temps = gcnew System::String(result->e[i].from);
						  ListViewItem ^item = gcnew ListViewItem(temps);
						  item->Tag = i;
						  item->SubItems->Add(gcnew System::String(result->e[i].to));
						  item->SubItems->Add(gcnew System::String(result->e[i].subject));
						  item->SubItems->Add(gcnew System::String(result->e[i].date));
						  if (client->MailBoxList[client->CurMailBox].inbox[i].r == false)
							  item->Font = gcnew System::Drawing::Font(item->Font, FontStyle::Bold);

						  listView1->Items->Add(item);
					  }
					  selectedFolder = 5;
		 }
private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {

			 selectedFolder = 5;
			 result = new SearchResult();
			 int k=0;
			 for (int i = 0; i < client->MailBoxList[client->CurMailBox].inbox.size(); i++)
			 {
				 if (CompareStrings(toolStripTextBox1->Text, client->MailBoxList[client->CurMailBox].inbox[i].to) || CompareStrings(toolStripTextBox1->Text, client->MailBoxList[client->CurMailBox].inbox[i].from) || CompareStrings(toolStripTextBox1->Text, client->MailBoxList[client->CurMailBox].inbox[i].subject))
				 {
					 result->e.push_back(client->MailBoxList[client->CurMailBox].inbox[i]);
					 k++;
				 }
			 }
			 MessageBox::Show("Íàéäåíî: " + k);
			 ShowSearchResult();
}
		 bool CompareStrings(String ^str1, char *str2)
		 {
			 int i = 0;
			 int l = 0;
			 while (i <  strlen(str2))
			 {
				 if (str1[l] == str2[i] && str1->Length > l)
					 l++;
			
				 if (l>=str1->Length)
					 return true;

				 i++;
			 }
			 return false;
		 }
private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 System::Windows::Forms::TreeNode^  treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 treeNode1 = treeView1->SelectedNode;
			 Ftype^ t = gcnew Ftype();
			 t = (Ftype^)treeNode1->Tag;
			 client->CurMailBox = t->MailboxNum;

				 if (treeNode1->Name == "Inbox")
					 selectedFolder = 0;
					 
				 if (treeNode1->Name == "Outbox")
					 selectedFolder = 1;
				 if (treeNode1->Name == "Spam")
					 selectedFolder = 2;
				
				 if (treeNode1->Name == "Trash")
					 selectedFolder = 3;

			//	 statusStrip1->Text = gcnew System::String(client->MailBoxList[client->CurMailBox].User);
				 toolStripStatusLabel2->Text = gcnew System::String(client->MailBoxList[client->CurMailBox].User);
				 this->PerformLayout();
}
};


}

