using System;
using System.Text.RegularExpressions;
using System.Windows.Forms;

using GameBoiManaged;

namespace GameBoi.Windows.Debugger
{
	public partial class MainWindow : Form
	{
		private GameBoyManaged mGameBoy;

		public MainWindow()
		{
			InitializeComponent();
		}

		private void textBoxReg_KeyPress(object sender, KeyPressEventArgs e)
		{
			string input = "" + e.KeyChar;
			string regex = "[0-9a-fA-F]";

			if (Char.IsControl(e.KeyChar) || Regex.IsMatch(input, regex))
			{
				e.Handled = false;
			}
			else
			{
				e.Handled = true;
			}
		}
	}
}
