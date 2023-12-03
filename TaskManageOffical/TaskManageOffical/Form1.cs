using System.Diagnostics;

namespace TaskManageOffical
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count > 0)
            {
                int selectedProcessId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);

                try
                {
                    Process selectedProcess = Process.GetProcessById(selectedProcessId);
                    selectedProcess.Kill();
                    // Sau khi chấm dứt tiến trình, bạn có thể làm mới danh sách để cập nhật DataGridView
                    listAllProcess();
                }
                catch (ArgumentException ex)
                {
                    Console.WriteLine($"Không tìm thấy tiến trình với Process ID {selectedProcessId}: {ex.Message}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Lỗi: {ex.Message}");
                }
            }
            else
            {
                MessageBox.Show("Vui lòng chọn một tiến trình để chấm dứt.", "Thông báo");
            }
        }


        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
        public void listAllProcess()
        {
            Process[] allProcess = Process.GetProcesses(); ;
            foreach (Process process in allProcess)
            {
                try
                {
                    dataGridView1.Rows.Add(process.Id, process.ProcessName, process.TotalProcessorTime, process.UserProcessorTime);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Lỗi: {ex.Message}");
                }
            }
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            listAllProcess();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listAllProcess();
        }

        private void runNewTaskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (Form2 f2 = new Form2())
            {
                if (f2.ShowDialog() == DialogResult.OK)
                {
                    listAllProcess();
                }
            }
        }
    }
}