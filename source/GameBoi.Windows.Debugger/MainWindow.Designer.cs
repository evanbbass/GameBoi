namespace GameBoi.Windows.Debugger
{
	partial class MainWindow
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.checkBoxCarryFlag = new System.Windows.Forms.CheckBox();
			this.checkBoxHalfCarryFlag = new System.Windows.Forms.CheckBox();
			this.checkBoxSubtractFlag = new System.Windows.Forms.CheckBox();
			this.checkBoxZeroFlag = new System.Windows.Forms.CheckBox();
			this.textBoxRegSP = new System.Windows.Forms.TextBox();
			this.labelRegSP = new System.Windows.Forms.Label();
			this.textBoxRegPC = new System.Windows.Forms.TextBox();
			this.labelRegPC = new System.Windows.Forms.Label();
			this.textBoxRegL = new System.Windows.Forms.TextBox();
			this.textBoxRegH = new System.Windows.Forms.TextBox();
			this.labelRegHL = new System.Windows.Forms.Label();
			this.textBoxRegE = new System.Windows.Forms.TextBox();
			this.textBoxRegD = new System.Windows.Forms.TextBox();
			this.labelRegDE = new System.Windows.Forms.Label();
			this.textBoxRegC = new System.Windows.Forms.TextBox();
			this.textBoxRegB = new System.Windows.Forms.TextBox();
			this.labelRegBC = new System.Windows.Forms.Label();
			this.textBoxRegF = new System.Windows.Forms.TextBox();
			this.textBoxRegA = new System.Windows.Forms.TextBox();
			this.labelRegAF = new System.Windows.Forms.Label();
			this.buttonStepCPU = new System.Windows.Forms.Button();
			this.buttonLoadCartridge = new System.Windows.Forms.Button();
			this.labelLastInstruction = new System.Windows.Forms.Label();
			this.textBoxLastInstruction = new System.Windows.Forms.TextBox();
			this.textBoxNextInstruction = new System.Windows.Forms.TextBox();
			this.labelNextInstruction = new System.Windows.Forms.Label();
			this.buttonReset = new System.Windows.Forms.Button();
			this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.checkBoxCarryFlag);
			this.groupBox1.Controls.Add(this.checkBoxHalfCarryFlag);
			this.groupBox1.Controls.Add(this.checkBoxSubtractFlag);
			this.groupBox1.Controls.Add(this.checkBoxZeroFlag);
			this.groupBox1.Controls.Add(this.textBoxRegSP);
			this.groupBox1.Controls.Add(this.labelRegSP);
			this.groupBox1.Controls.Add(this.textBoxRegPC);
			this.groupBox1.Controls.Add(this.labelRegPC);
			this.groupBox1.Controls.Add(this.textBoxRegL);
			this.groupBox1.Controls.Add(this.textBoxRegH);
			this.groupBox1.Controls.Add(this.labelRegHL);
			this.groupBox1.Controls.Add(this.textBoxRegE);
			this.groupBox1.Controls.Add(this.textBoxRegD);
			this.groupBox1.Controls.Add(this.labelRegDE);
			this.groupBox1.Controls.Add(this.textBoxRegC);
			this.groupBox1.Controls.Add(this.textBoxRegB);
			this.groupBox1.Controls.Add(this.labelRegBC);
			this.groupBox1.Controls.Add(this.textBoxRegF);
			this.groupBox1.Controls.Add(this.textBoxRegA);
			this.groupBox1.Controls.Add(this.labelRegAF);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(267, 197);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Registers";
			// 
			// checkBoxCarryFlag
			// 
			this.checkBoxCarryFlag.AutoSize = true;
			this.checkBoxCarryFlag.Location = new System.Drawing.Point(136, 108);
			this.checkBoxCarryFlag.Name = "checkBoxCarryFlag";
			this.checkBoxCarryFlag.Size = new System.Drawing.Size(95, 21);
			this.checkBoxCarryFlag.TabIndex = 14;
			this.checkBoxCarryFlag.Text = "Carry Flag";
			this.checkBoxCarryFlag.UseVisualStyleBackColor = true;
			this.checkBoxCarryFlag.CheckedChanged += new System.EventHandler(this.checkBoxCarryFlag_CheckedChanged);
			// 
			// checkBoxHalfCarryFlag
			// 
			this.checkBoxHalfCarryFlag.AutoSize = true;
			this.checkBoxHalfCarryFlag.Location = new System.Drawing.Point(136, 80);
			this.checkBoxHalfCarryFlag.Name = "checkBoxHalfCarryFlag";
			this.checkBoxHalfCarryFlag.Size = new System.Drawing.Size(125, 21);
			this.checkBoxHalfCarryFlag.TabIndex = 13;
			this.checkBoxHalfCarryFlag.Text = "Half-Carry Flag";
			this.checkBoxHalfCarryFlag.UseVisualStyleBackColor = true;
			this.checkBoxHalfCarryFlag.CheckedChanged += new System.EventHandler(this.checkBoxHalfCarryFlag_CheckedChanged);
			// 
			// checkBoxSubtractFlag
			// 
			this.checkBoxSubtractFlag.AutoSize = true;
			this.checkBoxSubtractFlag.Location = new System.Drawing.Point(136, 52);
			this.checkBoxSubtractFlag.Name = "checkBoxSubtractFlag";
			this.checkBoxSubtractFlag.Size = new System.Drawing.Size(114, 21);
			this.checkBoxSubtractFlag.TabIndex = 12;
			this.checkBoxSubtractFlag.Text = "Subtract Flag";
			this.checkBoxSubtractFlag.UseVisualStyleBackColor = true;
			this.checkBoxSubtractFlag.CheckedChanged += new System.EventHandler(this.checkBoxSubtractFlag_CheckedChanged);
			// 
			// checkBoxZeroFlag
			// 
			this.checkBoxZeroFlag.AutoSize = true;
			this.checkBoxZeroFlag.Location = new System.Drawing.Point(136, 24);
			this.checkBoxZeroFlag.Name = "checkBoxZeroFlag";
			this.checkBoxZeroFlag.Size = new System.Drawing.Size(91, 21);
			this.checkBoxZeroFlag.TabIndex = 11;
			this.checkBoxZeroFlag.Text = "Zero Flag";
			this.checkBoxZeroFlag.UseVisualStyleBackColor = true;
			this.checkBoxZeroFlag.CheckedChanged += new System.EventHandler(this.checkBoxZeroFlag_CheckedChanged);
			// 
			// textBoxRegSP
			// 
			this.textBoxRegSP.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegSP.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegSP.Location = new System.Drawing.Point(39, 134);
			this.textBoxRegSP.MaxLength = 4;
			this.textBoxRegSP.Name = "textBoxRegSP";
			this.textBoxRegSP.Size = new System.Drawing.Size(61, 24);
			this.textBoxRegSP.TabIndex = 9;
			this.textBoxRegSP.Text = "0000";
			this.textBoxRegSP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.toolTip1.SetToolTip(this.textBoxRegSP, "Stack Pointer");
			this.textBoxRegSP.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegSP.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegSP_Validating);
			// 
			// labelRegSP
			// 
			this.labelRegSP.AutoSize = true;
			this.labelRegSP.Location = new System.Drawing.Point(8, 137);
			this.labelRegSP.Name = "labelRegSP";
			this.labelRegSP.Size = new System.Drawing.Size(26, 17);
			this.labelRegSP.TabIndex = 14;
			this.labelRegSP.Text = "SP";
			this.toolTip1.SetToolTip(this.labelRegSP, "Stack Pointer");
			// 
			// textBoxRegPC
			// 
			this.textBoxRegPC.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegPC.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegPC.Location = new System.Drawing.Point(39, 162);
			this.textBoxRegPC.MaxLength = 4;
			this.textBoxRegPC.Name = "textBoxRegPC";
			this.textBoxRegPC.Size = new System.Drawing.Size(61, 24);
			this.textBoxRegPC.TabIndex = 10;
			this.textBoxRegPC.Text = "0000";
			this.textBoxRegPC.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.toolTip1.SetToolTip(this.textBoxRegPC, "Program Counter");
			this.textBoxRegPC.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegPC.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegPC_Validating);
			// 
			// labelRegPC
			// 
			this.labelRegPC.AutoSize = true;
			this.labelRegPC.Location = new System.Drawing.Point(8, 165);
			this.labelRegPC.Name = "labelRegPC";
			this.labelRegPC.Size = new System.Drawing.Size(26, 17);
			this.labelRegPC.TabIndex = 12;
			this.labelRegPC.Text = "PC";
			this.toolTip1.SetToolTip(this.labelRegPC, "Program Counter");
			// 
			// textBoxRegL
			// 
			this.textBoxRegL.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegL.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegL.Location = new System.Drawing.Point(70, 106);
			this.textBoxRegL.MaxLength = 2;
			this.textBoxRegL.Name = "textBoxRegL";
			this.textBoxRegL.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegL.TabIndex = 8;
			this.textBoxRegL.Text = "00";
			this.textBoxRegL.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegL.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegL.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegL_Validating);
			// 
			// textBoxRegH
			// 
			this.textBoxRegH.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegH.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegH.Location = new System.Drawing.Point(39, 106);
			this.textBoxRegH.MaxLength = 2;
			this.textBoxRegH.Name = "textBoxRegH";
			this.textBoxRegH.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegH.TabIndex = 7;
			this.textBoxRegH.Text = "00";
			this.textBoxRegH.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegH.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegH.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegH_Validating);
			// 
			// labelRegHL
			// 
			this.labelRegHL.AutoSize = true;
			this.labelRegHL.Location = new System.Drawing.Point(8, 109);
			this.labelRegHL.Name = "labelRegHL";
			this.labelRegHL.Size = new System.Drawing.Size(26, 17);
			this.labelRegHL.TabIndex = 9;
			this.labelRegHL.Text = "HL";
			// 
			// textBoxRegE
			// 
			this.textBoxRegE.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegE.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegE.Location = new System.Drawing.Point(70, 78);
			this.textBoxRegE.MaxLength = 2;
			this.textBoxRegE.Name = "textBoxRegE";
			this.textBoxRegE.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegE.TabIndex = 6;
			this.textBoxRegE.Text = "00";
			this.textBoxRegE.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegE.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegE.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegE_Validating);
			// 
			// textBoxRegD
			// 
			this.textBoxRegD.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegD.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegD.Location = new System.Drawing.Point(39, 78);
			this.textBoxRegD.MaxLength = 2;
			this.textBoxRegD.Name = "textBoxRegD";
			this.textBoxRegD.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegD.TabIndex = 5;
			this.textBoxRegD.Text = "00";
			this.textBoxRegD.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegD.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegD.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegD_Validating);
			// 
			// labelRegDE
			// 
			this.labelRegDE.AutoSize = true;
			this.labelRegDE.Location = new System.Drawing.Point(8, 81);
			this.labelRegDE.Name = "labelRegDE";
			this.labelRegDE.Size = new System.Drawing.Size(27, 17);
			this.labelRegDE.TabIndex = 6;
			this.labelRegDE.Text = "DE";
			// 
			// textBoxRegC
			// 
			this.textBoxRegC.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegC.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegC.Location = new System.Drawing.Point(70, 50);
			this.textBoxRegC.MaxLength = 2;
			this.textBoxRegC.Name = "textBoxRegC";
			this.textBoxRegC.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegC.TabIndex = 4;
			this.textBoxRegC.Text = "00";
			this.textBoxRegC.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegC.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegC.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegC_Validating);
			// 
			// textBoxRegB
			// 
			this.textBoxRegB.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegB.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegB.Location = new System.Drawing.Point(39, 50);
			this.textBoxRegB.MaxLength = 2;
			this.textBoxRegB.Name = "textBoxRegB";
			this.textBoxRegB.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegB.TabIndex = 3;
			this.textBoxRegB.Text = "00";
			this.textBoxRegB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegB.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegB.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegB_Validating);
			// 
			// labelRegBC
			// 
			this.labelRegBC.AutoSize = true;
			this.labelRegBC.Location = new System.Drawing.Point(8, 53);
			this.labelRegBC.Name = "labelRegBC";
			this.labelRegBC.Size = new System.Drawing.Size(26, 17);
			this.labelRegBC.TabIndex = 3;
			this.labelRegBC.Text = "BC";
			// 
			// textBoxRegF
			// 
			this.textBoxRegF.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegF.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegF.Location = new System.Drawing.Point(70, 22);
			this.textBoxRegF.MaxLength = 2;
			this.textBoxRegF.Name = "textBoxRegF";
			this.textBoxRegF.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegF.TabIndex = 2;
			this.textBoxRegF.Text = "00";
			this.textBoxRegF.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegF.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegF.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegF_Validating);
			// 
			// textBoxRegA
			// 
			this.textBoxRegA.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegA.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxRegA.Location = new System.Drawing.Point(39, 22);
			this.textBoxRegA.MaxLength = 2;
			this.textBoxRegA.Name = "textBoxRegA";
			this.textBoxRegA.Size = new System.Drawing.Size(30, 24);
			this.textBoxRegA.TabIndex = 1;
			this.textBoxRegA.Text = "00";
			this.textBoxRegA.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegA.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			this.textBoxRegA.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRegA_Validating);
			// 
			// labelRegAF
			// 
			this.labelRegAF.AutoSize = true;
			this.labelRegAF.Location = new System.Drawing.Point(8, 25);
			this.labelRegAF.Name = "labelRegAF";
			this.labelRegAF.Size = new System.Drawing.Size(25, 17);
			this.labelRegAF.TabIndex = 0;
			this.labelRegAF.Text = "AF";
			// 
			// buttonStepCPU
			// 
			this.buttonStepCPU.Location = new System.Drawing.Point(538, 176);
			this.buttonStepCPU.Name = "buttonStepCPU";
			this.buttonStepCPU.Size = new System.Drawing.Size(100, 30);
			this.buttonStepCPU.TabIndex = 15;
			this.buttonStepCPU.Text = "Step CPU";
			this.toolTip1.SetToolTip(this.buttonStepCPU, "Advance the CPU one step");
			this.buttonStepCPU.UseVisualStyleBackColor = true;
			this.buttonStepCPU.Click += new System.EventHandler(this.buttonStepCPU_Click);
			// 
			// buttonLoadCartridge
			// 
			this.buttonLoadCartridge.Location = new System.Drawing.Point(407, 176);
			this.buttonLoadCartridge.Name = "buttonLoadCartridge";
			this.buttonLoadCartridge.Size = new System.Drawing.Size(125, 30);
			this.buttonLoadCartridge.TabIndex = 16;
			this.buttonLoadCartridge.Text = "Load Cartridge...";
			this.toolTip1.SetToolTip(this.buttonLoadCartridge, "Load a cartridge into the emulator");
			this.buttonLoadCartridge.UseVisualStyleBackColor = true;
			this.buttonLoadCartridge.Click += new System.EventHandler(this.buttonLoadCartridge_Click);
			// 
			// labelLastInstruction
			// 
			this.labelLastInstruction.AutoSize = true;
			this.labelLastInstruction.Location = new System.Drawing.Point(285, 37);
			this.labelLastInstruction.Name = "labelLastInstruction";
			this.labelLastInstruction.Size = new System.Drawing.Size(104, 17);
			this.labelLastInstruction.TabIndex = 17;
			this.labelLastInstruction.Text = "Last Instruction";
			// 
			// textBoxLastInstruction
			// 
			this.textBoxLastInstruction.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxLastInstruction.Location = new System.Drawing.Point(288, 62);
			this.textBoxLastInstruction.Name = "textBoxLastInstruction";
			this.textBoxLastInstruction.ReadOnly = true;
			this.textBoxLastInstruction.Size = new System.Drawing.Size(350, 24);
			this.textBoxLastInstruction.TabIndex = 18;
			// 
			// textBoxNextInstruction
			// 
			this.textBoxNextInstruction.Font = new System.Drawing.Font("Lucida Console", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.textBoxNextInstruction.Location = new System.Drawing.Point(288, 118);
			this.textBoxNextInstruction.Name = "textBoxNextInstruction";
			this.textBoxNextInstruction.ReadOnly = true;
			this.textBoxNextInstruction.Size = new System.Drawing.Size(350, 24);
			this.textBoxNextInstruction.TabIndex = 20;
			// 
			// labelNextInstruction
			// 
			this.labelNextInstruction.AutoSize = true;
			this.labelNextInstruction.Location = new System.Drawing.Point(285, 93);
			this.labelNextInstruction.Name = "labelNextInstruction";
			this.labelNextInstruction.Size = new System.Drawing.Size(105, 17);
			this.labelNextInstruction.TabIndex = 19;
			this.labelNextInstruction.Text = "Next Instruction";
			// 
			// buttonReset
			// 
			this.buttonReset.Location = new System.Drawing.Point(326, 176);
			this.buttonReset.Name = "buttonReset";
			this.buttonReset.Size = new System.Drawing.Size(75, 30);
			this.buttonReset.TabIndex = 21;
			this.buttonReset.Text = "Reset";
			this.toolTip1.SetToolTip(this.buttonReset, "Reset the emulator");
			this.buttonReset.UseVisualStyleBackColor = true;
			this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
			// 
			// MainWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(650, 218);
			this.Controls.Add(this.buttonReset);
			this.Controls.Add(this.textBoxNextInstruction);
			this.Controls.Add(this.labelNextInstruction);
			this.Controls.Add(this.textBoxLastInstruction);
			this.Controls.Add(this.labelLastInstruction);
			this.Controls.Add(this.buttonLoadCartridge);
			this.Controls.Add(this.buttonStepCPU);
			this.Controls.Add(this.groupBox1);
			this.Name = "MainWindow";
			this.Text = "GameBoi Debugger";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox checkBoxCarryFlag;
		private System.Windows.Forms.CheckBox checkBoxHalfCarryFlag;
		private System.Windows.Forms.CheckBox checkBoxSubtractFlag;
		private System.Windows.Forms.CheckBox checkBoxZeroFlag;
		private System.Windows.Forms.TextBox textBoxRegSP;
		private System.Windows.Forms.Label labelRegSP;
		private System.Windows.Forms.TextBox textBoxRegPC;
		private System.Windows.Forms.Label labelRegPC;
		private System.Windows.Forms.TextBox textBoxRegL;
		private System.Windows.Forms.TextBox textBoxRegH;
		private System.Windows.Forms.Label labelRegHL;
		private System.Windows.Forms.TextBox textBoxRegE;
		private System.Windows.Forms.TextBox textBoxRegD;
		private System.Windows.Forms.Label labelRegDE;
		private System.Windows.Forms.TextBox textBoxRegC;
		private System.Windows.Forms.TextBox textBoxRegB;
		private System.Windows.Forms.Label labelRegBC;
		private System.Windows.Forms.TextBox textBoxRegF;
		private System.Windows.Forms.TextBox textBoxRegA;
		private System.Windows.Forms.Label labelRegAF;
		private System.Windows.Forms.Button buttonStepCPU;
		private System.Windows.Forms.Button buttonLoadCartridge;
		private System.Windows.Forms.Label labelLastInstruction;
		private System.Windows.Forms.TextBox textBoxLastInstruction;
		private System.Windows.Forms.TextBox textBoxNextInstruction;
		private System.Windows.Forms.Label labelNextInstruction;
		private System.Windows.Forms.Button buttonReset;
		private System.Windows.Forms.ToolTip toolTip1;
	}
}

