using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace TaskManageOffical
{
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }
        public static void Search(String Query)
        {
            string encodedQuery = System.Web.HttpUtility.UrlEncode(Query);
            Process.Start(new ProcessStartInfo("chrome.exe", "https://www.google.com.vn/search?q=" + encodedQuery) { UseShellExecute = true });
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Search(textBox1.Text);
        }
    }
}
