#include "MainWindow.h"

using namespace POP3_SMTP;

int main()
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew MainWindow());
	return 0;
}