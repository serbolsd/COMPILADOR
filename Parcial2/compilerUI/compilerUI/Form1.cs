using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reflection;
using System.Resources;
using System.Diagnostics;
using System.Management;
using System.Windows.Forms;

namespace compilerUI
{
    public partial class Form1 : Form
    {
        String DLLFullPath;
        dynamic compilerDLLInstance;
        bool isDLLLoaded;
        bool currentAssemblyisDebug;
        bool currentAssemblyIsx64;

        bool currentAssemblyisRelease;
        List<String> Token = new List<String>();
        List<String> symboltab = new List<String>();
        String str;
        public Form1()
        {
            isDLLLoaded = false;
            currentAssemblyisDebug = true;
            currentAssemblyisRelease = false;
            currentAssemblyIsx64 = false;
            InitializeComponent();
        }

        private bool loadCoompilerDLL()
        {
            String DLLFileNameDx64 = "Compilerx64d.dll";
            String DLLFileNameRx64 = "Compilerx64.dll";
            String DLLFileNameDx86 = "Compilerx86d.dll";
            String DLLFileNameRx86 = "Compilerx86.dll";
            String processFullPath = Process.GetCurrentProcess().MainModule.FileName; // Regresa la ruta completa del proceso donde esta la dll

            /* Search for debug x64 */
            String[] upstr = new String[6];
            DirectoryInfo up = Directory.GetParent(processFullPath);
            for (int i = 0; i < upstr.Length; i++)
            {
                upstr[i] = up.FullName;
                up = Directory.GetParent(upstr[i]);
                /* Debug */
                if (currentAssemblyisDebug && currentAssemblyIsx64)
                {

                    DLLFullPath = upstr[i] + "\\compilerUI\\x64\\Exe\\Debug\\" + DLLFileNameDx64;
                   // DLLFullPath = "C:\\Users\\sergi\\source\\repos\\Compiler\\x64\\Exe\\Debug\\" + DLLFileNameDx64;
                }
                else if (currentAssemblyisDebug)
                {
                    DLLFullPath = upstr[i] + "\\compilerUI\\x86\\Exe\\Debug\\" + DLLFileNameDx86;
                    //DLLFullPath = "C:\\Users\\sergi\\source\\repos\\Compiler\\x86\\Exe\\Debug\\" + DLLFileNameDx86;
                }
                /* Release */
                if (currentAssemblyisRelease && currentAssemblyIsx64)
                {
                    DLLFullPath = upstr[i] + "\\compilerUI\\x64\\Exe\\Release\\" + DLLFileNameRx64;
                    //DLLFullPath = "C:\\Users\\sergi\\source\\repos\\Compiler\\x64\\Exe\\Release\\" + DLLFileNameRx64;
                }
                else if (currentAssemblyisRelease)
                {
                    DLLFullPath = upstr[i] + "\\compilerUI\\x86\\Exe\\Release\\" + DLLFileNameRx86;
                    //DLLFullPath = "C:\\Users\\sergi\\source\\repos\\Compiler\\x86\\Exe\\Release\\" + DLLFileNameRx86;
                }
            }
            //DLLFullPath = up6str + "\\Compiler\\x64\\Exe\\Debug\\" + DLLFileName;
            var DLL = Assembly.UnsafeLoadFrom(DLLFullPath);

            var DLLType = DLL.GetType("Compiler.Manager");
            compilerDLLInstance = Activator.CreateInstance(DLLType);
            isDLLLoaded = compilerDLLInstance != null;


            return isDLLLoaded;
        }
        private void compilarProgramaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(isDLLLoaded)
            {
                textBox2.Text = "";
                String [] output = compilerDLLInstance.compileProgram(textBox1.Text);
                textBox2.Text = output[0];
                if (output[2] != null)
                {
                    textBox2.Text += "\r\n";
                    //textBox2.Text += "\n\r";
                    textBox2.Text += output[2];
                }
                else
                {
                    textBox2.Text += "\r\n";
                    //textBox2.Text += "\n\r";
                    textBox2.Text += "no se detectaron errores";
                }
                Update();
                dataGridView1.Rows.Clear();
                dataGridView2.Rows.Clear();
                String tokens = output[1];
                if(tokens!=null)
                {
                    for (int i = 0; i < tokens.Length; i++)
                    {
                        
                        if (tokens[i] != '\n')
                        {
                            str += tokens[i];
                            //i++;
                        }
                        if (tokens[i + 1] == '\n')
                        {
                            Token.Add(str);
                            str = "";
                            i++;
                        }
                        if (Token.Count == 3)
                        {
                            dataGridView1.Rows.Add(Token[0], Token[1], Token[2]);

                            Token.Clear();
                        }
                    }
                }
                String symbolTable= output[3];
                if (symbolTable != null)
                {
                    for (int i = 0; i < symbolTable.Length; i++)
                    {

                        if (symbolTable[i] != '\n')
                        {
                            str += symbolTable[i];
                            //i++;
                        }
                        if (symbolTable[i + 1] == '\n')
                        {
                            symboltab.Add(str);
                            str = "";
                            i++;
                        }
                        if (symboltab.Count == 6)
                        {
                            dataGridView2.Rows.Add(symboltab[0], symboltab[1], symboltab[2], symboltab[3], symboltab[4], symboltab[5]);

                            symboltab.Clear();
                        }
                    }
                }
            }
            else
            {
                string mesg = "No se pudo cargar la DLL";
                string name = "cargar DLL";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(mesg, name, buttons,MessageBoxIcon.Error);
                return;

            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            if(!loadCoompilerDLL())
            {
                string mesg = "No se pudo cargar la DLL";
                string name = "cargar DLL";
                MessageBoxButtons buttons = MessageBoxButtons.OK;
                DialogResult result = MessageBox.Show(mesg, name, buttons, MessageBoxIcon.Error);
                return;
            }

            isDLLLoaded = true;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void archvioToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void guardarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TextWriter txt = new StreamWriter("C:\\Users\\sergi\\source\\repos\\compilerUI\\doc.txt");
            txt.Write(textBox1.Text);
            txt.Close();
            System.Media.SystemSounds.Asterisk.Play();

            // taking full path of a file 
            string direction = "C:\\Users\\sergi\\source\\repos\\compilerUI\\doc.txt";

            // initialize the value of filename 
            string nameFile = Path.GetFileName(direction);

            label4.Text = nameFile;

            string text = System.IO.File.ReadAllText(direction);
            textBox2.Text = text;

        }


        private void habilitarAnalisisSemannticoToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

            label4.Text = null;
            string Dir = "C:\\Users\\sergi\\source\\repos\\compilerUI\\doc.txt";

            string name = Path.GetFileName(Dir);

            label4.Text = name;
        }

        private void salirToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (System.Windows.Forms.Application.MessageLoop)
            {
                // WinForms app
                System.Windows.Forms.Application.Exit();
            }
            else
            {
                // Console app
                System.Environment.Exit(1);
            }
        }

        private void guardarComo()
        {
            SaveFileDialog guardarComo = new SaveFileDialog();
            guardarComo.Filter = "Text File|*.txt|CPP File|*.cpp";
            guardarComo.Title = "Guardar Como...";
            guardarComo.ShowDialog();

            // If the file name is not an empty string open it for saving.  
            if (guardarComo.FileName != "")
            {
                using (StreamWriter Data = new StreamWriter(guardarComo.OpenFile()))
                {
                    Data.Write(textBox1.Text);
                }
            }
        }
        private void salirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            guardarComo();
        }

        private void abrirArchivo()
        {
            OpenFileDialog archivo = new OpenFileDialog();
            if (archivo.ShowDialog() == DialogResult.OK)
            {
                string data = File.ReadAllText(archivo.FileName);
                textBox1.Text = data;
                label4.Text = Path.GetFileName(archivo.FileName);
                textBox2.Text = "";
                dataGridView1.Rows.Clear();
                dataGridView2.Rows.Clear();
            }
        }

        private void abrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            abrirArchivo();
        }

        private void nuevoArchivo()
        {
            string mesg = "¿desea guardar los cambios?";
            string name = "CompilerUI";
            MessageBoxButtons buttons = MessageBoxButtons.YesNo;
            DialogResult result = MessageBox.Show(mesg, name, buttons);
            if (result == DialogResult.Yes)
            {
                guardarComo();
            }
            else
            {
                // Do something  
                textBox1.Text = "";
            }
        }

        private void nuevoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            dataGridView2.Rows.Clear();
            textBox2.Text = "";
            nuevoArchivo();

        }

      
    }
}
