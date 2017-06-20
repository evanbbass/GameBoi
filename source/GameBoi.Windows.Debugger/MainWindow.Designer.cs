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
			this.groupBox1.Size = new System.Drawing.Size(237, 197);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Registers";
			// 
			// checkBoxCarryFlag
			// 
			this.checkBoxCarryFlag.AutoSize = true;
			this.checkBoxCarryFlag.Location = new System.Drawing.Point(106, 108);
			this.checkBoxCarryFlag.Name = "checkBoxCarryFlag";
			this.checkBoxCarryFlag.Size = new System.Drawing.Size(95, 21);
			this.checkBoxCarryFlag.TabIndex = 20;
			this.checkBoxCarryFlag.Text = "Carry Flag";
			this.checkBoxCarryFlag.UseVisualStyleBackColor = true;
			// 
			// checkBoxHalfCarryFlag
			// 
			this.checkBoxHalfCarryFlag.AutoSize = true;
			this.checkBoxHalfCarryFlag.Location = new System.Drawing.Point(106, 80);
			this.checkBoxHalfCarryFlag.Name = "checkBoxHalfCarryFlag";
			this.checkBoxHalfCarryFlag.Size = new System.Drawing.Size(125, 21);
			this.checkBoxHalfCarryFlag.TabIndex = 19;
			this.checkBoxHalfCarryFlag.Text = "Half-Carry Flag";
			this.checkBoxHalfCarryFlag.UseVisualStyleBackColor = true;
			// 
			// checkBoxSubtractFlag
			// 
			this.checkBoxSubtractFlag.AutoSize = true;
			this.checkBoxSubtractFlag.Location = new System.Drawing.Point(106, 52);
			this.checkBoxSubtractFlag.Name = "checkBoxSubtractFlag";
			this.checkBoxSubtractFlag.Size = new System.Drawing.Size(114, 21);
			this.checkBoxSubtractFlag.TabIndex = 18;
			this.checkBoxSubtractFlag.Text = "Subtract Flag";
			this.checkBoxSubtractFlag.UseVisualStyleBackColor = true;
			// 
			// checkBoxZeroFlag
			// 
			this.checkBoxZeroFlag.AutoSize = true;
			this.checkBoxZeroFlag.Location = new System.Drawing.Point(106, 24);
			this.checkBoxZeroFlag.Name = "checkBoxZeroFlag";
			this.checkBoxZeroFlag.Size = new System.Drawing.Size(91, 21);
			this.checkBoxZeroFlag.TabIndex = 17;
			this.checkBoxZeroFlag.Text = "Zero Flag";
			this.checkBoxZeroFlag.UseVisualStyleBackColor = true;
			// 
			// textBoxRegSP
			// 
			this.textBoxRegSP.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegSP.Location = new System.Drawing.Point(39, 162);
			this.textBoxRegSP.MaxLength = 4;
			this.textBoxRegSP.Name = "textBoxRegSP";
			this.textBoxRegSP.Size = new System.Drawing.Size(61, 22);
			this.textBoxRegSP.TabIndex = 15;
			this.textBoxRegSP.Text = "0000";
			this.textBoxRegSP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegSP.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			// 
			// labelRegSP
			// 
			this.labelRegSP.AutoSize = true;
			this.labelRegSP.Location = new System.Drawing.Point(8, 165);
			this.labelRegSP.Name = "labelRegSP";
			this.labelRegSP.Size = new System.Drawing.Size(26, 17);
			this.labelRegSP.TabIndex = 14;
			this.labelRegSP.Text = "SP";
			// 
			// textBoxRegPC
			// 
			this.textBoxRegPC.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegPC.Location = new System.Drawing.Point(39, 134);
			this.textBoxRegPC.MaxLength = 4;
			this.textBoxRegPC.Name = "textBoxRegPC";
			this.textBoxRegPC.Size = new System.Drawing.Size(61, 22);
			this.textBoxRegPC.TabIndex = 13;
			this.textBoxRegPC.Text = "0000";
			this.textBoxRegPC.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegPC.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			// 
			// labelRegPC
			// 
			this.labelRegPC.AutoSize = true;
			this.labelRegPC.Location = new System.Drawing.Point(8, 137);
			this.labelRegPC.Name = "labelRegPC";
			this.labelRegPC.Size = new System.Drawing.Size(26, 17);
			this.labelRegPC.TabIndex = 12;
			this.labelRegPC.Text = "PC";
			// 
			// textBoxRegL
			// 
			this.textBoxRegL.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegL.Location = new System.Drawing.Point(70, 106);
			this.textBoxRegL.MaxLength = 2;
			this.textBoxRegL.Name = "textBoxRegL";
			this.textBoxRegL.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegL.TabIndex = 11;
			this.textBoxRegL.Text = "00";
			this.textBoxRegL.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegL.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			// 
			// textBoxRegH
			// 
			this.textBoxRegH.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegH.Location = new System.Drawing.Point(39, 106);
			this.textBoxRegH.MaxLength = 2;
			this.textBoxRegH.Name = "textBoxRegH";
			this.textBoxRegH.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegH.TabIndex = 10;
			this.textBoxRegH.Text = "00";
			this.textBoxRegH.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegH.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
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
			this.textBoxRegE.Location = new System.Drawing.Point(70, 78);
			this.textBoxRegE.MaxLength = 2;
			this.textBoxRegE.Name = "textBoxRegE";
			this.textBoxRegE.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegE.TabIndex = 8;
			this.textBoxRegE.Text = "00";
			this.textBoxRegE.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegE.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			// 
			// textBoxRegD
			// 
			this.textBoxRegD.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegD.Location = new System.Drawing.Point(39, 78);
			this.textBoxRegD.MaxLength = 2;
			this.textBoxRegD.Name = "textBoxRegD";
			this.textBoxRegD.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegD.TabIndex = 7;
			this.textBoxRegD.Text = "00";
			this.textBoxRegD.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegD.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
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
			this.textBoxRegC.Location = new System.Drawing.Point(70, 50);
			this.textBoxRegC.MaxLength = 2;
			this.textBoxRegC.Name = "textBoxRegC";
			this.textBoxRegC.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegC.TabIndex = 5;
			this.textBoxRegC.Text = "00";
			this.textBoxRegC.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegC.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			// 
			// textBoxRegB
			// 
			this.textBoxRegB.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegB.Location = new System.Drawing.Point(39, 50);
			this.textBoxRegB.MaxLength = 2;
			this.textBoxRegB.Name = "textBoxRegB";
			this.textBoxRegB.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegB.TabIndex = 4;
			this.textBoxRegB.Text = "00";
			this.textBoxRegB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegB.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
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
			this.textBoxRegF.Location = new System.Drawing.Point(70, 22);
			this.textBoxRegF.MaxLength = 2;
			this.textBoxRegF.Name = "textBoxRegF";
			this.textBoxRegF.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegF.TabIndex = 2;
			this.textBoxRegF.Text = "00";
			this.textBoxRegF.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegF.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
			// 
			// textBoxRegA
			// 
			this.textBoxRegA.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
			this.textBoxRegA.Location = new System.Drawing.Point(39, 22);
			this.textBoxRegA.MaxLength = 2;
			this.textBoxRegA.Name = "textBoxRegA";
			this.textBoxRegA.Size = new System.Drawing.Size(30, 22);
			this.textBoxRegA.TabIndex = 1;
			this.textBoxRegA.Text = "00";
			this.textBoxRegA.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.textBoxRegA.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxReg_KeyPress);
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
			// MainWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1006, 721);
			this.Controls.Add(this.groupBox1);
			this.Name = "MainWindow";
			this.Text = "GameBoi Debugger";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);

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
	}
}

