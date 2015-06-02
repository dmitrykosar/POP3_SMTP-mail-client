#ifndef SETTINGS_INCLUDED
#define SETTINGS_INCLUDED
#define BUFSIZE 4096


#include <iostream>
#include <vector>
#include <locale.h>
#include <stdio.h>
#include <fstream>
#include <Windows.h>
#include <process.h>
#include "easendmailobj.tlh"

using namespace EAGetMail;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Text;
using namespace System::Text::RegularExpressions;
using namespace System::Collections;
using namespace System::IO;

typedef struct MyData {
	char* info;
	bool Reader_Writer;
	HINSTANCE DLLdes;
} MYDATA, *PMYDATA;

 static public  class LogWriter {
public:
	
	
	HINSTANCE DLLdes;
	HANDLE hMutex, hFile;
	PMYDATA WriterData;
	void(*DLLFunc_Writer) (char *str, HANDLE hFile, HANDLE hMutex);
	void Init()
	{
		DLLdes = LoadLibrary(L"LogLibrary.dll");
		if (!DLLdes)
		{
			Console::OpenStandardOutput();
			Console::WriteLine("Library doesn't exist...");
			return ;
		}
		else
		{
			Console::OpenStandardOutput();
			Console::WriteLine("Library successfuly loaded...\n");
		}
	
		
		WriterData = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(MYDATA));
		if (WriterData == NULL)
		{
			Console::OpenStandardOutput();
			Console::WriteLine("Fail to create process data");
			return ;
		}
		WriterData->info = "Log.txt";
		WriterData->Reader_Writer = false;
		WriterData->DLLdes = DLLdes;
		DWORD dwWriterId;

		
		DLLFunc_Writer = (void(*) (char *str ,HANDLE hFile, HANDLE hMutex))GetProcAddress(DLLdes, "WriteLog");

		if (!DLLFunc_Writer)
		{
			System::Console::OpenStandardInput();
			Console::OpenStandardOutput();
			Console::WriteLine("ERROR!!!\n Function doesn't exists");
			return;
		}
		 hMutex = CreateMutex(NULL, FALSE, L"mut");
		 hFile = CreateFile(L"Log.txt", OPEN_EXISTING, 0, NULL, OPEN_ALWAYS, NULL, NULL);

	}
	 void Write(char *message)
	{
		 

		 if (!DLLFunc_Writer)
		 {
			 Console::OpenStandardOutput();
			 Console::WriteLine("ERROR!!!\n Function doesn't exists");
			 return;
		 }
		 DLLFunc_Writer(message,hFile,hMutex);
		 //WriteLog(message);
	}
	

	static unsigned __stdcall Thread(void *pParam) {

		HANDLE hFile;
		HANDLE hTempFile;
		DWORD  dwBytesRead, dwBytesWritten, dwBufSize = BUFSIZE;
		char szTempName[MAX_PATH];
		char buffer[BUFSIZE];
		char lpPathBuffer[BUFSIZE];

		// Откроем существующий файл. 

		hFile = CreateFile((LPCWSTR)"logfile.txt",  // имя файла 
			GENERIC_READ,                   // открыт для чтения 
			0,                              // совместного использования нет 
			NULL,                           // защита по умолчанию 
			OPEN_ALWAYS,                  // только существующий файл 
			FILE_ATTRIBUTE_NORMAL,          // атрибуты обычного файла 
			NULL);                          // шаблона атрибутов нет 
		if (hFile == INVALID_HANDLE_VALUE)
		{
	//		ReleaseMutex(hMutex);
			return 0;
		}

		DWORD WrittenBytes;
		char *str = (char*)pParam;
		if (!WriteFile(hFile, str, strlen(str), &WrittenBytes, NULL))
		{
	//		ReleaseMutex(hMutex);
			return 0;
		}
	//	ReleaseMutex(hMutex);
	}

	void LogWriterExit()
	{
		CloseHandle(hFile);
		CloseHandle(hMutex);
		FreeLibrary(DLLdes);
	}

};
public class logwr{
public:
	LogWriter lw;
	int init = 0;
	logwr()
	{
		if (!init)
			lw.Init();
	}
	void Write(char *msg)
	{
		lw.Write(msg);
	}
};
public class attachment {
public:
	attachment(char* n, char* p)
	{
		strcpy_s(name, n);
		strcpy_s(path, p);
	}

	attachment()
	{

	}
	char name[500];
	char path[500];
};

public class eMail {
public:
	char *from, *to, *subject, *body;
	bool r;
	char *date, *file;
	vector<attachment> attachments;
	
public:
	eMail()
	{
		this->r = true;
		this->from = new char[50];
		this->to = new char[250];
		this->subject = new char[100];
		this->date = new char[50];
		this->body = new char[5000];
	}
	eMail(char* from, char* to, char* subject, char* file, char* date, bool r)
	{
		this->r = r;
		this->from = new char[50];
		this->to = new char[250];
		this->subject = new char[100];
		this->date = new char[50];
		strcpy_s(this->from,50, from);
		strcpy_s(this->subject,100, subject);
		strcpy_s(this->to, 50, to);
		strcpy_s(this->date, 50, date);
	}
};

public class MailBox {

public:
	
	char MailBoxName[50];
	char User[100];
	char Pass[100];
	char pop3_server[100];
	char smtp_server[100];
	vector<eMail> inbox;
	vector<eMail> outbox;
	vector<eMail> spam;
	vector<eMail> trash;
	logwr lg;
	MailBox(char *MailBoxName, char *User, char *Pass, char *pop3, char *smtp)
	{
		strcpy_s(this->MailBoxName, MailBoxName);
		strcpy_s(this->User, User);
		strcpy_s(this->Pass, Pass);
		strcpy_s(this->pop3_server, pop3);
		strcpy_s(this->smtp_server, smtp);
		lg.Write(CreateLogMessage("Added\n"));
	}
	char* CreateLogMessage(char *msg)
	{
		System::DateTime d = System::DateTime::Now;
		System::Globalization::CultureInfo ^cur = gcnew
			System::Globalization::CultureInfo("en-US");
		String ^sdate = d.ToString("yyyy.MM.dd.HH.mm.ss", cur);
		sdate = sdate + " : mailbox: " + gcnew System::String(this->User) + "-> "+ gcnew System::String(msg);
		char *message = (char*)calloc(sdate->Length, sizeof(char));
		strcpy_s(message, sdate->Length+strlen(msg),(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sdate));
		return message;
	}
	int DownloadAndSave()
	{
		//lg.Write(CreateLogMessage("Downloading inbox messages"));
		String ^curpath = Directory::GetCurrentDirectory();
		String ^str = gcnew System::String("{0}\\");
		str = gcnew System::String(this->MailBoxName) +"\\" + "inbox";
		String ^mailbox = String::Format(str, curpath);

		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);

		}

		int Count;
		MailServer ^oServer = gcnew MailServer(gcnew System::String(this->pop3_server),
			gcnew System::String(this->User), gcnew System::String(this->Pass), ServerProtocol::Pop3);
		MailClient ^oClient = gcnew MailClient("TryIt");


		oServer->SSLConnection = true;
		oServer->Port = 995;

		try
		{

			oClient->Connect(oServer);
			array<MailInfo^> ^infos;
			try {
				infos = oClient->GetMailInfos(); throw 1;
			}
			catch (int a)
			{
				
				
			}

			if (infos->Length == 0)
				return 0;
			Count = infos->Length;
			for (int i = 0; i < infos->Length; i++)
			{
				MailInfo ^info = infos[i];
				Console::WriteLine("Index: {0}; Size: {1}; UIDL: {2}",
					info->Index, info->Size, info->UIDL);

				// Receive email from POP3 server
				Mail ^oMail = oClient->GetMail(info);

				Console::WriteLine("From: {0}", oMail->From->ToString());
				Console::WriteLine("Subject: {0}\r\n", oMail->Subject);

				// Generate an email file name based on date time.
				System::DateTime d = System::DateTime::Now;
				System::Globalization::CultureInfo ^cur = gcnew
					System::Globalization::CultureInfo("en-US");
				String ^sdate = d.ToString("yyyyMMddHHmmss", cur);
				String ^fileName = String::Format("{0}\\{1}{2}{3}",
					mailbox, sdate, d.Millisecond.ToString("d3"), i);

				// Save email to local disk
				oMail->SaveAs(fileName+".eml", true);
				
				array<Attachment^>^ atts = oMail->Attachments;

		


				String ^a1 = oMail->From->ToString();
				char *temp1 = new char[100];
				char *temp2 = new char[100];
				char *temp3 = new char[100];
				char *temp4 = new char[100];
				char *temp5 = new char[25];
				temp1 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(oMail->From->ToString());
		
				temp3 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(oMail->Subject);
				temp4 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName);
				temp5 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(oMail->ReceivedDate.ToString("yyyy-MM-dd HH:mm:ss"));
				a1 = oMail->HtmlBody->ToString();

				eMail tmpeMail(temp1, this->User, temp3, temp4, temp5, false);
				String ^fullfName = fileName + ".eml";
				tmpeMail.file = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fullfName);
				String ^fileName1 = gcnew String(fileName + ".eml");
				try
				{
					int pos = fileName1->LastIndexOf(".");
					String ^mainName = fileName1->Substring(0, pos);
					String ^htmlName = mainName + ".htm";
					String ^tempFolder = mainName;
					if (!File::Exists(htmlName))
					{
						// We haven't generate the html for this email, generate it now.
						tmpeMail.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(_GenerateHtmlForEmail(htmlName, fileName1, tempFolder));
					}

					
				}
				catch (Exception ^ep)
				{
					Console::WriteLine(ep->Message);
				}
				if (atts->Length > 0)
				{
					if (!Directory::Exists(curpath + "\\" + fileName))
					Directory::CreateDirectory(curpath + "\\" + fileName);
					for (int i = 0; i < atts->Length; i++)
					{
						Attachment ^att = atts[i];

						att->SaveAs(curpath + "\\" + fileName + "\\" + att->Name, true);
						char *temp;
						temp = new char[500];
						attachment at;
						strcpy_s(at.name, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(att->Name));
						strcpy_s(at.path, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(curpath + "\\" + fileName + "\\" + att->Name));
						tmpeMail.attachments.push_back(at);
					}
				}
			
				inbox.push_back(tmpeMail);

				// Mark email as deleted from POP3 server.
			//	oClient->Delete(info);

			}
		}
		catch (int a){}

		// Quit and pure emails marked as deleted from POP3 server.
		oClient->Quit();
		return Count;

	}
	void SaveOutMail(eMail em)
	{
		EASendMail::SmtpMail ^oMail = gcnew EASendMail::SmtpMail("TryIt");
		System::String ^curpath = Directory::GetCurrentDirectory();
		System::String ^str = gcnew System::String("{0}\\");
		System::String^ user = gcnew System::String(this->MailBoxName);
		str = user + "\\" + "outbox";
		System::String ^mailbox = String::Format(str, curpath);

		// If the folder is not existed, create it.
		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);
		}
		for (int i = 0; i < em.attachments.size(); i++)
		oMail->AddAttachment(gcnew System::String(em.attachments[i].path));

		oMail->From = gcnew System::String(gcnew System::String(this->User));
		oMail->To = gcnew System::String(em.to);
		oMail->Subject = gcnew System::String(em.subject);
		oMail->HtmlBody = gcnew System::String(em.body);
		System::DateTime d = System::DateTime::Now;
		System::Globalization::CultureInfo ^cur = gcnew
			System::Globalization::CultureInfo("en-US");
		System::String ^sdate = d.ToString("yyyyMMddHHmmss", cur);
		System::String ^fileName = String::Format("{0}\\{1}{2}{3}.eml",
			mailbox, sdate, d.Millisecond.ToString("d3"), 0);
		System::String ^fileName2 = String::Format("{0}\\{1}{2}{3}.txt",
			mailbox, sdate, d.Millisecond.ToString("d3"), 0);
		em.date = (char*)(void*)Marshal::StringToHGlobalAnsi(d.ToString("yyyy MM dd HH:mm:ss", cur));

		// Save email to local disk
		oMail->SaveAs(fileName, true);

	}
	bool SendeMail(eMail e)
	{
		
					::CoInitialize(NULL);
			char error[100];
			EASendMailObjLib::IMailPtr oSmtp = NULL;
		oSmtp.CreateInstance("EASendMailObj.Mail");
		oSmtp->LicenseCode = ("TryIt");

		oSmtp->FromAddr = (_bstr_t)(this->User);

		oSmtp->AddRecipientEx(e.to, 0);

		oSmtp->Subject = (e.subject);

		oSmtp->BodyText = e.body;
		oSmtp->ServerPort = 465;
		if (e.attachments.size() > 0)
		{
			for (int i = 0; i < e.attachments.size(); i++)
			if (oSmtp->AddAttachment(e.attachments[i].path) != 0)
			strcpy_s(error ,	oSmtp->GetLastErrDescription());
		}


		oSmtp->ServerAddr = this->smtp_server;

		oSmtp->UserName = this->User;
		oSmtp->Password = this->Pass;

		oSmtp->SSL_init();
		bool result = oSmtp->SendMail();
		if (result == 0)
		{

			outbox.push_back(e);
			SaveOutMail(e);
		}
		else

		strcpy_s(error, oSmtp->GetLastErrDescription());
		//Console::WriteLine("failed to send email with the following error:");

		if (oSmtp != NULL)
			oSmtp.Release();
		return result;

	}
	String^ _GenerateHtmlForEmail(String ^htmlName, String ^emlFile, String ^tempFolder)
	{
		Mail ^oMail = gcnew Mail("TryIt");
		oMail->Load(emlFile, false);

		if (oMail->IsEncrypted)
		{
			try
			{
				// This email is encrypted, we decrypt it by user default certificate.
				// you can also use specified certificate like this
				// Certificate ^oCert = gcnew Certificate();
				// oCert->Load("c:\\test.pfx", "pfxpassword",
				//	Certificate::CertificateKeyLocation::CRYPT_USER_KEYSET);
				// oMail = oMail->Decrypt( oCert );
				oMail = oMail->Decrypt(nullptr);
			}
			catch (Exception ^ep)
			{
				Console::WriteLine(ep->Message);
				oMail->Load(emlFile, false);
			}
		}

		if (oMail->IsSigned)
		{
			try
			{
				// This email is digital signed.
				EAGetMail::Certificate ^cert = oMail->VerifySignature();
				Console::WriteLine("This email contains a valid digital signature.");

				// You can add the certificate to your certificate storage like this
				// cert->AddToStore( 
				// Certificate::CertificateStoreLocation::CERT_SYSTEM_STORE_CURRENT_USER,
				//	"addressbook" );
				// then you can use send the encrypted email back to this sender.
			}
			catch (Exception ^ep)
			{
				Console::WriteLine(ep->Message);
			}
		}

		// Decode winmail.dat (TNEF) and RTF body (convert RTF to HTML) automatically
		oMail->DecodeTNEF();

		String ^html = oMail->HtmlBody;
		StringBuilder ^hdr = gcnew StringBuilder();

		hdr->Append("<font face=\"Courier New,Arial\" size=2>");
		int count;

		array<Attachment^>^ atts = oMail->Attachments;
		count = atts->Length;
		if (count > 0)
		{
			if (!Directory::Exists(tempFolder))
				Directory::CreateDirectory(tempFolder);

			hdr->Append("<b>Attachments:</b>");
			for (int i = 0; i < count; i++)
			{
				Attachment ^att = atts[i];

				String ^attname = String::Format("{0}\\{1}", tempFolder, att->Name);
				att->SaveAs(attname, true);
				hdr->Append(String::Format("<a href=\"{0}\" target=\"_blank\">{1}</a> ",
					attname, att->Name));
				String^ simage = "image/";
				if (att->ContentID->Length > 0)
				{
					// Show embedded image.
					html = html->Replace(String::Format("cid:{0}", att->ContentID), attname);
				}
				else if (String::Compare(att->ContentType, 0,
					"image/", 0, simage->Length, true) == 0)
				{
					// show attached image.
					html = String::Concat(html,
						String::Format("<hr><img src=\"{0}\">", attname));
				}
			}
		}

		Regex ^reg = gcnew Regex("(<meta[^>]*charset[ \t]*=[ \t\"]*)([^<> \r\n\"]*)",
			(RegexOptions)(RegexOptions::Multiline | RegexOptions::IgnoreCase));
		html = reg->Replace(html, "$1utf-8");
		if (!reg->IsMatch(html))
		{
			hdr->Insert(0,
				"<meta HTTP-EQUIV=\"Content-Type\" Content=\"text-html; charset=utf-8\">");
		}

		html = html->Insert(0, "<hr>");
		html = html->Insert(0, hdr->ToString());
		
		FileStream ^fs = gcnew FileStream(htmlName,
			FileMode::Create, FileAccess::Write, FileShare::None);
		array<unsigned char>^ data = System::Text::UTF8Encoding::UTF8->GetBytes(html);
		fs->Write(data, 0, data->Length);
		fs->Close();
		oMail->Clear();
		return html;
	}
	String^ _FormatHtmlTag(String ^src)
	{
		src = src->Replace(">", "&gt;");
		src = src->Replace("<", "&lt;");
		return src;
	}
	void SaveMailStatus()
	{
		String ^user = gcnew System::String(this->User);
		String ^mailFolder = gcnew System::String("{0}\\");
		String ^str;
		mailFolder = gcnew System::String(MailBoxName) + "\\" + "inbox";
		if (!Directory::Exists(mailFolder))
			Directory::CreateDirectory(mailFolder);
		for (int i = 0; i<inbox.size(); i++)
		{
			if (inbox[i].r == true)
			{
				str = str + "1";
			}
			else
			{
				str = str + "0";
			}

		}
		if (inbox.size()>0)
		{
			FileStream ^fs = gcnew FileStream(mailFolder + "\\" + "mailstatus.txt",
				FileMode::Create, FileAccess::Write, FileShare::None);
			array<unsigned char>^ data = System::Text::UTF8Encoding::UTF8->GetBytes(str);


			fs->Write(data, 0, data->Length);

			fs->Close();
		}
	}
	void LoadExistMails()
	{
		String ^curpath = Directory::GetCurrentDirectory();
		String ^str = gcnew System::String("{0}\\");
		str = gcnew System::String(this->MailBoxName) + "\\" + "inbox";
		String ^mailbox = String::Format(str, curpath);

		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);
		}
		array<String^>^files = Directory::GetFiles(str, "*.eml");
		int count = files->Length;
		fstream fstr;
		char c;

		fstr.open((char*)(void*)Marshal::StringToHGlobalAnsi(str + "\\" + "mailstatus.txt"), ios::in | ios::out);
		for (int i = 0; i < count; i++)
		{

			bool red;
			String ^fullname = files[i];
			Mail ^oMail = gcnew Mail("TryIt");
			oMail->Load(fullname, true);
			if (!fstr.eof() && fstr.read(&c, sizeof(char)))
			{
				if (c == '0')
					red = false;
				else
					red = true;
			}

			eMail em((char*)(void*)Marshal::StringToHGlobalAnsi(oMail->From->ToString()),
				User,
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->Subject),
				(char*)(void*)Marshal::StringToHGlobalAnsi(fullname),
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->ReceivedDate.ToString("yyyy-MM-dd HH:mm:ss")),
				red
				);	
			em.file = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fullname);
			String ^fileName1 = gcnew String(str + ".eml");
			try
			{
				int pos = fullname->LastIndexOf(".");
				String ^mainName = fullname->Substring(0, pos);
				String ^htmlName = mainName + ".htm";
				String ^tempFolder = mainName;
				
		
				String ^htmlbody = _GenerateHtmlForEmail(htmlName, fullname, tempFolder);
					em.body = (char*)calloc(htmlbody->Length+1 , sizeof(char));
				em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(htmlbody);
				


			}
			catch (Exception ^ep)
			{
				Console::WriteLine(ep->Message);
			}
			array<Attachment^>^ atts = oMail->Attachments;
			for (int i = 0; i < atts->Length; i++)
			{
				Attachment ^att = atts[i];

				char *temp;
				temp = new char[500];
				attachment at;
				strcpy_s(at.name, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(att->Name));
				strcpy_s(at.path, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(curpath + "\\" + str + "\\" + att->Name));
				em.attachments.push_back(at);
			}
			inbox.push_back(em);
		}
		fstr.close();
		str = gcnew System::String(this->MailBoxName) + "\\" + "outbox";
		mailbox = String::Format(str, curpath);

		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);
		}
		files = Directory::GetFiles(str, "*.eml");
	 count = files->Length;
		for (int i = 0; i < count; i++)
		{

			
			String ^fullname = files[i];
			Mail ^oMail = gcnew Mail("TryIt");
			oMail->Load(fullname, true);
		

			eMail em((char*)(void*)Marshal::StringToHGlobalAnsi(oMail->From->ToString()),
				User,
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->Subject),
				(char*)(void*)Marshal::StringToHGlobalAnsi(fullname),
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->ReceivedDate.ToString("yyyy-MM-dd HH:mm:ss")),
				true
				);
			String ^fileName1 = gcnew String(str + ".eml");
			try
			{
				int pos = fullname->LastIndexOf(".");
				String ^mainName = fullname->Substring(0, pos);
				String ^htmlName = mainName + ".htm";
				String ^tempFolder = mainName;
				em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(oMail->HtmlBody);
				if (!File::Exists(htmlName))
				{
					// We haven't generate the html for this email, generate it now.
					em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(_GenerateHtmlForEmail(htmlName, fullname, tempFolder));
				}


			}
			catch (Exception ^ep)
			{
				Console::WriteLine(ep->Message);
			}
			array<Attachment^>^ atts = oMail->Attachments;
			for (int i = 0; i < atts->Length; i++)
			{
				Attachment ^att = atts[i];

				char *temp;
				temp = new char[500];
				attachment at;
				strcpy_s(at.name, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(att->Name));
				strcpy_s(at.path, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(curpath + "\\" + str + "\\" + att->Name));
				em.attachments.push_back(at);
			}
				outbox.push_back(em);
		}
		str = gcnew System::String(this->MailBoxName) + "\\" + "spam";
		mailbox = String::Format(str, curpath);

		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);
		}
		files = Directory::GetFiles(str, "*.eml");
		count = files->Length;
		for (int i = 0; i < count; i++)
		{


			String ^fullname = files[i];
			Mail ^oMail = gcnew Mail("TryIt");
			oMail->Load(fullname, true);


			eMail em((char*)(void*)Marshal::StringToHGlobalAnsi(oMail->From->ToString()),
				User,
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->Subject),
				(char*)(void*)Marshal::StringToHGlobalAnsi(fullname),
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->ReceivedDate.ToString("yyyy-MM-dd HH:mm:ss")),
				true
				);
		
			try
			{
				int pos = fullname->LastIndexOf(".");
				String ^mainName = fullname->Substring(0, pos);
				String ^htmlName = mainName + ".htm";
				String ^tempFolder = mainName;
				em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(oMail->HtmlBody);
				if (!File::Exists(htmlName))
				{
					// We haven't generate the html for this email, generate it now.
					em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(_GenerateHtmlForEmail(htmlName, fullname, tempFolder));
				}


			}
			catch (Exception ^ep)
			{
				Console::WriteLine(ep->Message);
			}
			array<Attachment^>^ atts = oMail->Attachments;
			for (int i = 0; i < atts->Length; i++)
			{
				Attachment ^att = atts[i];

				char *temp;
				temp = new char[500];
				attachment at;
				strcpy_s(at.name, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(att->Name));
				strcpy_s(at.path, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(curpath + "\\" + str + "\\" + att->Name));
				em.attachments.push_back(at);
			}
			spam.push_back(em);
		}
		str = gcnew System::String(this->MailBoxName) + "\\" + "trash";
		mailbox = String::Format(str, curpath);

		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);
		}
		files = Directory::GetFiles(str, "*.eml");
		count = files->Length;
		for (int i = 0; i < count; i++)
		{


			String ^fullname = files[i];
			Mail ^oMail = gcnew Mail("TryIt");
			oMail->Load(fullname, true);


			eMail em((char*)(void*)Marshal::StringToHGlobalAnsi(oMail->From->ToString()),
				User,
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->Subject),
				(char*)(void*)Marshal::StringToHGlobalAnsi(fullname),
				(char*)(void*)Marshal::StringToHGlobalAnsi(oMail->ReceivedDate.ToString("yyyy-MM-dd HH:mm:ss")),
				true
				);
			String ^fileName1 = gcnew String(str + ".eml");
			try
			{
				int pos = fullname->LastIndexOf(".");
				String ^mainName = fullname->Substring(0, pos);
				String ^htmlName = mainName + ".htm";
				String ^tempFolder = mainName;
				em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(oMail->HtmlBody);
				em.file = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fullname);
				if (!File::Exists(htmlName))
				{
					// We haven't generate the html for this email, generate it now.
					em.body = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(_GenerateHtmlForEmail(htmlName, fullname, tempFolder));
				}


			}
			catch (Exception ^ep)
			{
				Console::WriteLine(ep->Message);
			}
			array<Attachment^>^ atts = oMail->Attachments;
			for (int i = 0; i < atts->Length; i++)
			{
				Attachment ^att = atts[i];

				char *temp;
				temp = new char[500];
				attachment at;
				strcpy_s(at.name, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(att->Name));
				strcpy_s(at.path, 500, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(curpath + "\\" + str + "\\" + att->Name));
				em.attachments.push_back(at);
			}
			trash.push_back(em);
		}
	}
	void AddToSpam(int index)
	{
		
		String ^curpath = Directory::GetCurrentDirectory();
		String ^str = gcnew System::String("{0}\\");

		String ^path = String::Format(str, curpath);
		curpath =curpath + "\\" + gcnew System::String(this->inbox[index].file);

		if (!Directory::Exists(path))
		{
			lg.Write(CreateLogMessage("Error adding to spam\n"));
			return;
		}

		System::IO::File::Delete(curpath);

		curpath = Directory::GetCurrentDirectory();
		str = gcnew System::String("{0}\\");
		str = gcnew System::String(this->MailBoxName) + "\\" + "spam";
		String ^mailbox = String::Format(str, curpath);

		if (!Directory::Exists(mailbox))
		{
			Directory::CreateDirectory(mailbox);

		}
		eMail em = inbox[index];
		EASendMail::SmtpMail ^oMail = gcnew EASendMail::SmtpMail("TryIt");

		for (int i = 0; i < em.attachments.size(); i++)
			oMail->AddAttachment(gcnew System::String(em.attachments[i].path));

		oMail->From = gcnew System::String(gcnew System::String(em.from));
		oMail->To = gcnew System::String(em.to);
		oMail->Subject = gcnew System::String(em.subject);
		oMail->HtmlBody = gcnew System::String(em.body);
		System::DateTime d = System::DateTime::Now;
		System::Globalization::CultureInfo ^cur = gcnew
			System::Globalization::CultureInfo("en-US");
		System::String ^sdate = d.ToString("yyyyMMddHHmmss", cur);
		System::String ^fileName = String::Format("{0}\\{1}{2}{3}.eml",
			mailbox, sdate, d.Millisecond.ToString("d3"), 0);
		
		em.date = (char*)(void*)Marshal::StringToHGlobalAnsi(d.ToString("yyyy MM dd HH:mm:ss", cur));

		// Save email to local disk
		oMail->SaveAs(fileName, true);

		spam.push_back(em);
		inbox.erase(inbox.begin() + index);

		
	}
	void AddToTrash(int folder, int index)
	{
		eMail em;
		switch (folder)
		{
		case 0:
		{
				  String ^curpath = Directory::GetCurrentDirectory();
				  String ^str = gcnew System::String("{0}\\");

				  String ^path = String::Format(str, curpath);
				  curpath = curpath + "\\" + gcnew System::String(this->inbox[index].file);

				  if (!Directory::Exists(path))
				  {
					  lg.Write(CreateLogMessage("Error adding to trash\n"));
					  return;
				  }
				  System::IO::File::Delete(curpath);
				  em = inbox[index];
				  inbox.erase(inbox.begin() + index);
		}
				break;
		case 1:
		{
				  String ^curpath = Directory::GetCurrentDirectory();
				  String ^str = gcnew System::String("{0}\\");

				  String ^path = String::Format(str, curpath);
				  curpath = curpath + "\\" + gcnew System::String(this->outbox[index].file);

				  if (!Directory::Exists(path))
				  {
					  lg.Write(CreateLogMessage("Error adding to trash\n"));
					  return;
				  }
				  System::IO::File::Delete(curpath);
				 em = outbox[index];
				 outbox.erase(outbox.begin() + index);
		}
				break;
		case 2:
		{
				  String ^curpath = Directory::GetCurrentDirectory();
				  String ^str = gcnew System::String("{0}\\");

				  String ^path = String::Format(str, curpath);
				  curpath = curpath + "\\" + gcnew System::String(this->spam[index].file);

				  if (!Directory::Exists(path))
				  {
					  lg.Write(CreateLogMessage("Error adding to trash\n"));
					  return;
				  }
				  System::IO::File::Delete(curpath);
				 em = spam[index];
				 spam.erase(spam.begin() + index);
		}
				break;
		}
		String ^curpath = Directory::GetCurrentDirectory();
		String ^str = gcnew System::String("{0}\\");
		str = gcnew System::String(this->MailBoxName) + "\\" + "trash";
		String ^mailbox = String::Format(str, curpath);
		EASendMail::SmtpMail ^oMail = gcnew EASendMail::SmtpMail("TryIt");

		for (int i = 0; i < em.attachments.size(); i++)
			oMail->AddAttachment(gcnew System::String(em.attachments[i].path));

		oMail->From = gcnew System::String(gcnew System::String(em.from));
		oMail->To = gcnew System::String(em.to);
		oMail->Subject = gcnew System::String(em.subject);
		oMail->HtmlBody = gcnew System::String(em.body);
		System::DateTime d = System::DateTime::Now;
		System::Globalization::CultureInfo ^cur = gcnew
			System::Globalization::CultureInfo("en-US");
		System::String ^sdate = d.ToString("yyyyMMddHHmmss", cur);
		System::String ^fileName = String::Format("{0}\\{1}{2}{3}.eml",
			mailbox, sdate, d.Millisecond.ToString("d3"), 0);

		em.date = (char*)(void*)Marshal::StringToHGlobalAnsi(d.ToString("yyyy MM dd HH:mm:ss", cur));
		em.file = (char*)(void*)Marshal::StringToHGlobalAnsi(fileName);
		// Save email to local disk
		oMail->SaveAs(fileName, true);

		trash.push_back(em);
	}
	void DeleteMail(int index)
	{
		String ^curpath = Directory::GetCurrentDirectory();
		String ^str = gcnew System::String("{0}\\");
		str = gcnew System::String(this->MailBoxName) + "\\" + "trash";
		String ^mailbox = String::Format(str, curpath);
		String ^path = String::Format(str, curpath);

		curpath = curpath + "\\" + gcnew System::String(this->trash[index].file);

		if (!Directory::Exists(path))
		{
			lg.Write(CreateLogMessage("Error adding to trash\n"));
			return;
		}

		System::IO::File::Delete(curpath);
	
		trash.erase(trash.begin() + index);

	}

};
struct  MailboxInfo
{
	char *name, *pass, *smtp, *pop3;
public:
	MailboxInfo(MailBox m)
	{
		name = m.User;
		pass = m.Pass;
		smtp = m.smtp_server;
		pop3 = m.pop3_server;
	}

};
public class Client
{
public:
	
	
	int CurMailBox;
	vector<MailBox> MailBoxList;
	Client()
	{
		
		CurMailBox = -1;
	}
	void SaveClientStatus()
	{
		for (int i = 0; i < MailBoxList.size(); i++)
		{
			MailBoxList[i].SaveMailStatus();
		}
	}
	void SaveMailboxes()
	{
		FileStream ^fs = gcnew FileStream("Client.txt",
			FileMode::Create, FileAccess::Write, FileShare::None);
		for (int i = 0; i < MailBoxList.size(); i++)
		{

			
			String ^str =  gcnew System::String(this->MailBoxList[i].MailBoxName);
			
			MailboxInfo m(MailBoxList[i]);
			
			str = str + " " + gcnew System::String(this->MailBoxList[i].User) + " " + gcnew System::String(this->MailBoxList[i].Pass) + " " + gcnew System::String(this->MailBoxList[i].pop3_server)  + " "
				+ gcnew System::String(this->MailBoxList[i].smtp_server) + " ";
			array<unsigned char>^ data = System::Text::UTF8Encoding::UTF8->GetBytes(str);
			fs->Write(data, 0, data->Length);

		

		}
		fs->Close();
	}
	void LoadMailboxes()
	{
		fstream fs;
		fs.open("Client.txt", ios::in | ios::out);

		//	FileStream ^fs = gcnew FileStream("Client.txt",
		//	FileMode::Open, FileAccess::Write, FileShare::None);
		//	array<unsigned char>^ data;
		System::String ^str;
		int i = 0;
		char *s = (char*)calloc(250, sizeof(char));
		char c;

		while (!fs.eof() && fs.read(&c, sizeof(char)))
		{


			str += Convert::ToChar(c);
			i++;
			//c = (char*)calloc(1, sizeof(char));
		}
		fs.close();
		if (str)
		{

			array<System::String^>^ inf;
			inf = str->Split(' ');

			if (inf->Length > 4)
			for (int i = 0; i < inf->Length-1; i += 5)
			{
				MailBox m((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(inf[i]),
					(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(inf[i + 1]),
					(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(inf[i + 2]),
					(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(inf[i + 3]),
					(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(inf[i + 4])
					);
				m.LoadExistMails();
				this->MailBoxList.push_back(m);
			

			}
			
		}
	}
	
	
};

public ref class Ftype {
public:
	int MailboxNum;
	int type;
};

public class SearchResult {
public:
	vector<eMail> e;
};
#endif

