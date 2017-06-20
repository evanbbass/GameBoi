#pragma once

//#include "GameBoy.h"

namespace GameBoiDebugger {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//using namespace GameBoi;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(/*GameBoy& gameBoy*/) //:
			//mGameBoy(gameBoy)
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
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		//GameBoi::GameBoy& mGameBoy;

	private: System::Windows::Forms::GroupBox^  groupBoxRegisters;
	protected:
	private: System::Windows::Forms::TextBox^  textBoxRegSP;
	private: System::Windows::Forms::Label^  labelRegSP;
	private: System::Windows::Forms::TextBox^  textBoxRegPC;
	private: System::Windows::Forms::Label^  labelRegPC;
	private: System::Windows::Forms::TextBox^  textBoxRegL;
	private: System::Windows::Forms::TextBox^  textBoxRegH;
	private: System::Windows::Forms::Label^  labelRegHL;
	private: System::Windows::Forms::TextBox^  textBoxRegE;
	private: System::Windows::Forms::TextBox^  textBoxRegD;
	private: System::Windows::Forms::Label^  labelRegDE;
	private: System::Windows::Forms::TextBox^  textBoxRegC;
	private: System::Windows::Forms::TextBox^  textBoxRegB;
	private: System::Windows::Forms::Label^  labelRegBC;
	private: System::Windows::Forms::TextBox^  textBoxRegF;
	private: System::Windows::Forms::TextBox^  textBoxRegA;
	private: System::Windows::Forms::Label^  labelRegAF;
	private: System::Windows::Forms::CheckBox^  checkBoxCarryFlag;
	private: System::Windows::Forms::CheckBox^  checkBoxHalfCarryFlag;
	private: System::Windows::Forms::CheckBox^  checkBoxSubtractFlag;
	private: System::Windows::Forms::CheckBox^  checkBoxZeroFlag;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->groupBoxRegisters = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxCarryFlag = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxHalfCarryFlag = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSubtractFlag = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxZeroFlag = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxRegSP = (gcnew System::Windows::Forms::TextBox());
			this->labelRegSP = (gcnew System::Windows::Forms::Label());
			this->textBoxRegPC = (gcnew System::Windows::Forms::TextBox());
			this->labelRegPC = (gcnew System::Windows::Forms::Label());
			this->textBoxRegL = (gcnew System::Windows::Forms::TextBox());
			this->textBoxRegH = (gcnew System::Windows::Forms::TextBox());
			this->labelRegHL = (gcnew System::Windows::Forms::Label());
			this->textBoxRegE = (gcnew System::Windows::Forms::TextBox());
			this->textBoxRegD = (gcnew System::Windows::Forms::TextBox());
			this->labelRegDE = (gcnew System::Windows::Forms::Label());
			this->textBoxRegC = (gcnew System::Windows::Forms::TextBox());
			this->textBoxRegB = (gcnew System::Windows::Forms::TextBox());
			this->labelRegBC = (gcnew System::Windows::Forms::Label());
			this->textBoxRegF = (gcnew System::Windows::Forms::TextBox());
			this->textBoxRegA = (gcnew System::Windows::Forms::TextBox());
			this->labelRegAF = (gcnew System::Windows::Forms::Label());
			this->groupBoxRegisters->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBoxRegisters
			// 
			this->groupBoxRegisters->Controls->Add(this->checkBoxCarryFlag);
			this->groupBoxRegisters->Controls->Add(this->checkBoxHalfCarryFlag);
			this->groupBoxRegisters->Controls->Add(this->checkBoxSubtractFlag);
			this->groupBoxRegisters->Controls->Add(this->checkBoxZeroFlag);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegSP);
			this->groupBoxRegisters->Controls->Add(this->labelRegSP);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegPC);
			this->groupBoxRegisters->Controls->Add(this->labelRegPC);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegL);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegH);
			this->groupBoxRegisters->Controls->Add(this->labelRegHL);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegE);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegD);
			this->groupBoxRegisters->Controls->Add(this->labelRegDE);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegC);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegB);
			this->groupBoxRegisters->Controls->Add(this->labelRegBC);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegF);
			this->groupBoxRegisters->Controls->Add(this->textBoxRegA);
			this->groupBoxRegisters->Controls->Add(this->labelRegAF);
			this->groupBoxRegisters->Location = System::Drawing::Point(13, 13);
			this->groupBoxRegisters->Name = L"groupBoxRegisters";
			this->groupBoxRegisters->Size = System::Drawing::Size(245, 197);
			this->groupBoxRegisters->TabIndex = 0;
			this->groupBoxRegisters->TabStop = false;
			this->groupBoxRegisters->Text = L"Registers";
			// 
			// checkBoxCarryFlag
			// 
			this->checkBoxCarryFlag->AutoSize = true;
			this->checkBoxCarryFlag->Location = System::Drawing::Point(101, 108);
			this->checkBoxCarryFlag->Name = L"checkBoxCarryFlag";
			this->checkBoxCarryFlag->Size = System::Drawing::Size(95, 21);
			this->checkBoxCarryFlag->TabIndex = 20;
			this->checkBoxCarryFlag->Text = L"Carry Flag";
			this->checkBoxCarryFlag->UseVisualStyleBackColor = true;
			// 
			// checkBoxHalfCarryFlag
			// 
			this->checkBoxHalfCarryFlag->AutoSize = true;
			this->checkBoxHalfCarryFlag->Location = System::Drawing::Point(101, 80);
			this->checkBoxHalfCarryFlag->Name = L"checkBoxHalfCarryFlag";
			this->checkBoxHalfCarryFlag->Size = System::Drawing::Size(125, 21);
			this->checkBoxHalfCarryFlag->TabIndex = 19;
			this->checkBoxHalfCarryFlag->Text = L"Half-Carry Flag";
			this->checkBoxHalfCarryFlag->UseVisualStyleBackColor = true;
			// 
			// checkBoxSubtractFlag
			// 
			this->checkBoxSubtractFlag->AutoSize = true;
			this->checkBoxSubtractFlag->Location = System::Drawing::Point(101, 52);
			this->checkBoxSubtractFlag->Name = L"checkBoxSubtractFlag";
			this->checkBoxSubtractFlag->Size = System::Drawing::Size(114, 21);
			this->checkBoxSubtractFlag->TabIndex = 18;
			this->checkBoxSubtractFlag->Text = L"Subtract Flag";
			this->checkBoxSubtractFlag->UseVisualStyleBackColor = true;
			// 
			// checkBoxZeroFlag
			// 
			this->checkBoxZeroFlag->AutoSize = true;
			this->checkBoxZeroFlag->Location = System::Drawing::Point(101, 24);
			this->checkBoxZeroFlag->Name = L"checkBoxZeroFlag";
			this->checkBoxZeroFlag->Size = System::Drawing::Size(91, 21);
			this->checkBoxZeroFlag->TabIndex = 17;
			this->checkBoxZeroFlag->Text = L"Zero Flag";
			this->checkBoxZeroFlag->UseVisualStyleBackColor = true;
			// 
			// textBoxRegSP
			// 
			this->textBoxRegSP->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegSP->Location = System::Drawing::Point(39, 162);
			this->textBoxRegSP->MaxLength = 4;
			this->textBoxRegSP->Name = L"textBoxRegSP";
			this->textBoxRegSP->Size = System::Drawing::Size(56, 22);
			this->textBoxRegSP->TabIndex = 15;
			this->textBoxRegSP->Text = L"0000";
			this->textBoxRegSP->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegSP->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// labelRegSP
			// 
			this->labelRegSP->AutoSize = true;
			this->labelRegSP->Location = System::Drawing::Point(8, 165);
			this->labelRegSP->Name = L"labelRegSP";
			this->labelRegSP->Size = System::Drawing::Size(26, 17);
			this->labelRegSP->TabIndex = 14;
			this->labelRegSP->Text = L"SP";
			// 
			// textBoxRegPC
			// 
			this->textBoxRegPC->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegPC->Location = System::Drawing::Point(39, 134);
			this->textBoxRegPC->MaxLength = 4;
			this->textBoxRegPC->Name = L"textBoxRegPC";
			this->textBoxRegPC->Size = System::Drawing::Size(56, 22);
			this->textBoxRegPC->TabIndex = 13;
			this->textBoxRegPC->Text = L"0000";
			this->textBoxRegPC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegPC->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// labelRegPC
			// 
			this->labelRegPC->AutoSize = true;
			this->labelRegPC->Location = System::Drawing::Point(8, 137);
			this->labelRegPC->Name = L"labelRegPC";
			this->labelRegPC->Size = System::Drawing::Size(26, 17);
			this->labelRegPC->TabIndex = 12;
			this->labelRegPC->Text = L"PC";
			// 
			// textBoxRegL
			// 
			this->textBoxRegL->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegL->Location = System::Drawing::Point(70, 106);
			this->textBoxRegL->MaxLength = 2;
			this->textBoxRegL->Name = L"textBoxRegL";
			this->textBoxRegL->Size = System::Drawing::Size(25, 22);
			this->textBoxRegL->TabIndex = 11;
			this->textBoxRegL->Text = L"00";
			this->textBoxRegL->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegL->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// textBoxRegH
			// 
			this->textBoxRegH->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegH->Location = System::Drawing::Point(39, 106);
			this->textBoxRegH->MaxLength = 2;
			this->textBoxRegH->Name = L"textBoxRegH";
			this->textBoxRegH->Size = System::Drawing::Size(25, 22);
			this->textBoxRegH->TabIndex = 10;
			this->textBoxRegH->Text = L"00";
			this->textBoxRegH->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegH->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// labelRegHL
			// 
			this->labelRegHL->AutoSize = true;
			this->labelRegHL->Location = System::Drawing::Point(8, 109);
			this->labelRegHL->Name = L"labelRegHL";
			this->labelRegHL->Size = System::Drawing::Size(26, 17);
			this->labelRegHL->TabIndex = 9;
			this->labelRegHL->Text = L"HL";
			// 
			// textBoxRegE
			// 
			this->textBoxRegE->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegE->Location = System::Drawing::Point(70, 78);
			this->textBoxRegE->MaxLength = 2;
			this->textBoxRegE->Name = L"textBoxRegE";
			this->textBoxRegE->Size = System::Drawing::Size(25, 22);
			this->textBoxRegE->TabIndex = 8;
			this->textBoxRegE->Text = L"00";
			this->textBoxRegE->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegE->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// textBoxRegD
			// 
			this->textBoxRegD->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegD->Location = System::Drawing::Point(39, 78);
			this->textBoxRegD->MaxLength = 2;
			this->textBoxRegD->Name = L"textBoxRegD";
			this->textBoxRegD->Size = System::Drawing::Size(25, 22);
			this->textBoxRegD->TabIndex = 7;
			this->textBoxRegD->Text = L"00";
			this->textBoxRegD->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegD->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// labelRegDE
			// 
			this->labelRegDE->AutoSize = true;
			this->labelRegDE->Location = System::Drawing::Point(8, 81);
			this->labelRegDE->Name = L"labelRegDE";
			this->labelRegDE->Size = System::Drawing::Size(27, 17);
			this->labelRegDE->TabIndex = 6;
			this->labelRegDE->Text = L"DE";
			// 
			// textBoxRegC
			// 
			this->textBoxRegC->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegC->Location = System::Drawing::Point(70, 50);
			this->textBoxRegC->MaxLength = 2;
			this->textBoxRegC->Name = L"textBoxRegC";
			this->textBoxRegC->Size = System::Drawing::Size(25, 22);
			this->textBoxRegC->TabIndex = 5;
			this->textBoxRegC->Text = L"00";
			this->textBoxRegC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegC->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// textBoxRegB
			// 
			this->textBoxRegB->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegB->Location = System::Drawing::Point(39, 50);
			this->textBoxRegB->MaxLength = 2;
			this->textBoxRegB->Name = L"textBoxRegB";
			this->textBoxRegB->Size = System::Drawing::Size(25, 22);
			this->textBoxRegB->TabIndex = 4;
			this->textBoxRegB->Text = L"00";
			this->textBoxRegB->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegB->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// labelRegBC
			// 
			this->labelRegBC->AutoSize = true;
			this->labelRegBC->Location = System::Drawing::Point(8, 53);
			this->labelRegBC->Name = L"labelRegBC";
			this->labelRegBC->Size = System::Drawing::Size(26, 17);
			this->labelRegBC->TabIndex = 3;
			this->labelRegBC->Text = L"BC";
			// 
			// textBoxRegF
			// 
			this->textBoxRegF->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegF->Location = System::Drawing::Point(70, 22);
			this->textBoxRegF->MaxLength = 2;
			this->textBoxRegF->Name = L"textBoxRegF";
			this->textBoxRegF->Size = System::Drawing::Size(25, 22);
			this->textBoxRegF->TabIndex = 2;
			this->textBoxRegF->Text = L"00";
			this->textBoxRegF->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegF->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// textBoxRegA
			// 
			this->textBoxRegA->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->textBoxRegA->Location = System::Drawing::Point(39, 22);
			this->textBoxRegA->MaxLength = 2;
			this->textBoxRegA->Name = L"textBoxRegA";
			this->textBoxRegA->Size = System::Drawing::Size(25, 22);
			this->textBoxRegA->TabIndex = 1;
			this->textBoxRegA->Text = L"00";
			this->textBoxRegA->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxRegA->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBoxReg_KeyPress);
			// 
			// labelRegAF
			// 
			this->labelRegAF->AutoSize = true;
			this->labelRegAF->Location = System::Drawing::Point(8, 25);
			this->labelRegAF->Name = L"labelRegAF";
			this->labelRegAF->Size = System::Drawing::Size(25, 17);
			this->labelRegAF->TabIndex = 0;
			this->labelRegAF->Text = L"AF";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1006, 721);
			this->Controls->Add(this->groupBoxRegisters);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainWindow";
			this->Text = L"GameBoi Debugger";
			this->groupBoxRegisters->ResumeLayout(false);
			this->groupBoxRegisters->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void textBoxReg_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
};
}
