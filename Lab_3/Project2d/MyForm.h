#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#define PI 3.14159265
#pragma once

namespace Project2d {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenTK::Platform::Windows;
	using namespace OpenTK::Graphics::OpenGL;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: OpenTK::GLControl^  glControl1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  startToolStripMenuItem;





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
			this->glControl1 = (gcnew OpenTK::GLControl());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->startToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// glControl1
			// 
			this->glControl1->BackColor = System::Drawing::Color::Black;
			this->glControl1->Location = System::Drawing::Point(12, 27);
			this->glControl1->Name = L"glControl1";
			this->glControl1->Size = System::Drawing::Size(803, 330);
			this->glControl1->TabIndex = 0;
			this->glControl1->VSync = false;
			this->glControl1->Load += gcnew System::EventHandler(this, &MyForm::glControl1_Load);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->startToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(827, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// startToolStripMenuItem
			// 
			this->startToolStripMenuItem->Name = L"startToolStripMenuItem";
			this->startToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->startToolStripMenuItem->Text = L"Start";
			this->startToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::startToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(827, 369);
			this->Controls->Add(this->glControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

	}


private: System::Void startToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			 GL::ClearColor(Color::White);
			 int w = glControl1->Width;
			 int h = glControl1->Height;
			 GL::MatrixMode(MatrixMode::Projection);
			 GL::LoadIdentity();
			 GL::Ortho(0, w, 0, h, -1, 1); 
			 GL::Viewport(0, 0, w, h);

			 GL::Clear(ClearBufferMask::ColorBufferBit | ClearBufferMask::DepthBufferBit);

			 GL::MatrixMode(MatrixMode::Modelview);
			 GL::LoadIdentity();
			 for (float i = 0.0; i <= glControl1->Width; i += 1.0){
				 //----------------------------------------------------------------------
				 GL::Color3(Color::LightSkyBlue);
				 for (float j = 0.0; j < glControl1->Width * 2 - 1; j++)
				 {
					 GL::Begin(BeginMode::Polygon);
					 GL::Vertex2(j / 2, (float)sin(j*PI / 180) * 30 + glControl1->Height / 2);
					 GL::Vertex2((j + 1) / 2,(float)sin((j+1)*PI / 180) * 30 + glControl1->Height / 2);
					 GL::Vertex2((j+1)/2, 0.0f);
					 GL::Vertex2(j/2, 0.0f);
					 GL::End();
				 }
				 //--------------------------------------------------------------------
				 GL::Color3(Color::Yellow);
				 GL::Begin(BeginMode::Polygon);
				 int posX=100, posY=glControl1->Height-50;
				 GL::Vertex2(posX,posY);
				 double _tmpPoint; int radius = 20;
				 for (int i = 0; i <= radius; i++)
				 {
					 _tmpPoint = (float)i / radius * PI * 2;
					 GL::Vertex2(posX + cos(_tmpPoint) * (radius),posY + sin(_tmpPoint) * (radius));
				 }
				 GL::End();
				 //--------------------------------------------------------------------
				 GL::Color3(Color::Red);
				 GL::Begin(BeginMode::Triangles);
				 GL::Vertex2((i + glControl1->Width) / 2, (float)sin((i + glControl1->Width)*PI / 180) * 30 + glControl1->Height / 2);
				 GL::Vertex2((i + glControl1->Width) / 2 - 20, (float)sin((i + glControl1->Width)*PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::Vertex2((i + glControl1->Width) / 2 + 20, (float)sin((i + glControl1->Width)*PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::End();

				 GL::Color3(Color::Green);
				 GL::Begin(BeginMode::Polygon);
				 GL::Vertex2((i + glControl1->Width) / 2 - 10, (float)sin((i + glControl1->Width)* PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::Vertex2((i + glControl1->Width) / 2 + 10, (float)sin((i + glControl1->Width)*PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::Vertex2((i + glControl1->Width) / 2 + 10, (float)sin((i + glControl1->Width)*PI / 180) * 30 + glControl1->Height / 2 + 25);
				 GL::Vertex2((i + glControl1->Width) / 2 - 10, (float)sin((i + glControl1->Width)*PI / 180) * 30 + glControl1->Height / 2 + 25);
				 GL::End();
				 //---------------------------------------------------------------
				 GL::Color3(Color::Red);
				 GL::Begin(BeginMode::Triangles);
				 GL::Vertex2((glControl1->Width - i) / 2, (float)sin((glControl1->Width - i)*PI / 180) * 30 + glControl1->Height / 2);
				 GL::Vertex2((glControl1->Width - i) / 2 - 20, (float)sin((glControl1->Width - i)*PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::Vertex2((glControl1->Width - i) / 2 + 20, (float)sin((glControl1->Width - i)*PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::End();

				 GL::Color3(Color::Green);
				 GL::Begin(BeginMode::Polygon);
				 GL::Vertex2((glControl1->Width - i) / 2 - 10, (float)sin((glControl1->Width - i)* PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::Vertex2((glControl1->Width - i) / 2 + 10, (float)sin((glControl1->Width - i)*PI / 180) * 30 + glControl1->Height / 2 + 15);
				 GL::Vertex2((glControl1->Width - i) / 2 + 10, (float)sin((glControl1->Width - i)*PI / 180) * 30 + glControl1->Height / 2 + 25);
				 GL::Vertex2((glControl1->Width - i) / 2 - 10, (float)sin((glControl1->Width - i)*PI / 180) * 30 + glControl1->Height / 2 + 25);
				 GL::End();
				 //---------------------------------------------------------------
				 Thread::Sleep(1);
				 glControl1->SwapBuffers();
				 GL::Clear(ClearBufferMask::ColorBufferBit);
			 }
			 }
private: System::Void glControl1_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
