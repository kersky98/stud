#pragma once
#include<stdio.h>
#include<winsock2.h>
//#include "stdAfx.h"
#include "stddef.h"
//#pragma comment(lib,"ws2_32.lib") //Winsock Library

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
namespace ChatOnFriday {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  myTextBox;
	private: System::Windows::Forms::RichTextBox^  TextBox;
	protected: 


	private: System::Windows::Forms::Button^  button1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->myTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->TextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// myTextBox
			// 
			this->myTextBox->Location = System::Drawing::Point(12, 247);
			this->myTextBox->Name = L"myTextBox";
			this->myTextBox->Size = System::Drawing::Size(471, 76);
			this->myTextBox->TabIndex = 0;
			this->myTextBox->Text = L"";
			// 
			// TextBox
			// 
			this->TextBox->Location = System::Drawing::Point(12, 12);
			this->TextBox->Name = L"TextBox";
			this->TextBox->ReadOnly = true;
			this->TextBox->Size = System::Drawing::Size(471, 229);
			this->TextBox->TabIndex = 1;
			this->TextBox->Text = L"";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 330);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 24);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Отправить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(495, 366);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->TextBox);
			this->Controls->Add(this->myTextBox);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
		 

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 struct sockaddr_in si_other;
				 int s, slen = sizeof(si_other);
				 char buf[BUFLEN];
				 char message[BUFLEN] = { 0 };
				 WSADATA wsa;
				 String^ bufer;


	//Initialise winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		exit(EXIT_FAILURE);
	}

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
		bufer = myTextBox->Text;
		int i = 0;
		int buffflen = bufer->Length;
		while (buffflen>0)
		{
			message[i] = Convert::ToChar(bufer[0]);
			bufer = bufer->Remove(0, 1);
			i++;
			buffflen--;
		}
		bufer = myTextBox->Text;
		TextBox->Text = TextBox->Text + bufer+ "\n\n";
		myTextBox->Text="";
		
		//send the message
		if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			exit(EXIT_FAILURE);
		}

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			exit(EXIT_FAILURE);
		}

		puts(buf);
		
	closesocket(s);
	WSACleanup();




			 }
	};
}

