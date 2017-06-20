using System;
using System.Globalization;
using System.Text.RegularExpressions;
using System.Windows.Forms;

using GameBoiManaged;

namespace GameBoi.Windows.Debugger
{
	public partial class MainWindow : Form
	{
		private readonly GameBoyManaged mGameBoy;

		public MainWindow()
		{
			mGameBoy = new GameBoyManaged();
			InitializeComponent();
			UpdateFields();
		}

		private void textBoxReg_KeyPress(object sender, KeyPressEventArgs e)
		{
			string input = "" + e.KeyChar;
			const string regex = "[0-9a-fA-F]";

			if (Char.IsControl(e.KeyChar) || Regex.IsMatch(input, regex))
			{
				e.Handled = false;
			}
			else
			{
				e.Handled = true;
			}
		}

		private void UpdateFields()
		{
			RegistersManaged registers = mGameBoy.CPU.Registers;
			textBoxRegA.Text = registers.A.ToString("X2");
			textBoxRegF.Text = registers.F.ToString("X2");
			textBoxRegB.Text = registers.B.ToString("X2");
			textBoxRegC.Text = registers.C.ToString("X2");
			textBoxRegD.Text = registers.D.ToString("X2");
			textBoxRegE.Text = registers.E.ToString("X2");
			textBoxRegH.Text = registers.H.ToString("X2");
			textBoxRegL.Text = registers.L.ToString("X2");
			textBoxRegSP.Text = registers.SP.ToString("X4");
			textBoxRegPC.Text = registers.PC.ToString("X4");
			checkBoxZeroFlag.Checked = registers.ZeroFlag;
			checkBoxSubtractFlag.Checked = registers.SubtractFlag;
			checkBoxHalfCarryFlag.Checked = registers.HalfCarryFlag;
			checkBoxCarryFlag.Checked = registers.CarryFlag;
		}

		private void buttonStepCPU_Click(object sender, EventArgs e)
		{
			mGameBoy.CPU.StepCPU();
			UpdateFields();
		}

		private void textBoxRegA_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.A = Byte.Parse(textBoxRegA.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegF_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.F = Byte.Parse(textBoxRegF.Text, NumberStyles.HexNumber);
			mGameBoy.CPU.Registers.F &= 0xF0;
			UpdateFields();
		}

		private void textBoxRegB_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.B = Byte.Parse(textBoxRegB.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegC_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.C = Byte.Parse(textBoxRegC.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegD_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.D = Byte.Parse(textBoxRegD.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegE_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.E = Byte.Parse(textBoxRegE.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegH_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.H = Byte.Parse(textBoxRegH.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegL_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.L = Byte.Parse(textBoxRegL.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegSP_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.SP = UInt16.Parse(textBoxRegSP.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void textBoxRegPC_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			mGameBoy.CPU.Registers.PC = UInt16.Parse(textBoxRegPC.Text, NumberStyles.HexNumber);
			UpdateFields();
		}

		private void checkBoxZeroFlag_CheckedChanged(object sender, EventArgs e)
		{
			mGameBoy.CPU.Registers.ZeroFlag = checkBoxZeroFlag.Checked;
			UpdateFields();
		}

		private void checkBoxSubtractFlag_CheckedChanged(object sender, EventArgs e)
		{
			mGameBoy.CPU.Registers.SubtractFlag = checkBoxSubtractFlag.Checked;
			UpdateFields();
		}

		private void checkBoxHalfCarryFlag_CheckedChanged(object sender, EventArgs e)
		{
			mGameBoy.CPU.Registers.HalfCarryFlag = checkBoxHalfCarryFlag.Checked;
			UpdateFields();
		}

		private void checkBoxCarryFlag_CheckedChanged(object sender, EventArgs e)
		{
			mGameBoy.CPU.Registers.CarryFlag = checkBoxCarryFlag.Checked;
			UpdateFields();
		}
	}
}
