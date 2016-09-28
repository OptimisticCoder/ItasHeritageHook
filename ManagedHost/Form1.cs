using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;

namespace ManagedHost
{
    public partial class Form1 : Form
    {
        [DllImport("../../../Debug/ItasHeritageHook.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "StartHook")]
        public static extern void StartHook(IntPtr hwnd);

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            StartHook(this.Handle);
        }
    }
}
