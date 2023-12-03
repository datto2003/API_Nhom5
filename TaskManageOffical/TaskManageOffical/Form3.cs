using Microsoft.Office.Interop.Word;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Word = Microsoft.Office.Interop.Word;
namespace TaskManageOffical
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Word.Application word = new Word.Application();
                word.Visible = true;
                word.WindowState = Word.WdWindowState.wdWindowStateNormal;
                Word.Document doc = word.Documents.Add();
                Word.Paragraph paragraph = doc.Paragraphs.Add();
                paragraph.Range.Text = richTextBox1.Text;

                // Lấy tên tập tin từ TextBox
                string fileName = textBox1.Text.Trim();

                // Kiểm tra xem tên tập tin có hợp lệ không
                if (string.IsNullOrWhiteSpace(fileName))
                {
                    MessageBox.Show("Vui lòng nhập tên tập tin.", "Thông báo");
                    return;
                }

                // Đảm bảo rằng tên tập tin có đuôi .doc
                if (!fileName.ToLower().EndsWith(".doc"))
                {
                    fileName += ".doc";
                }

                // Kiểm tra xem đường dẫn có tồn tại không, nếu không thì tạo mới
                string filePath = Path.Combine(@"C:\TestWord", fileName);
                string directoryPath = Path.GetDirectoryName(filePath);
                if (!Directory.Exists(directoryPath))
                {
                    Directory.CreateDirectory(directoryPath);
                }

                // Lưu tài liệu Word với tên tập tin đã nhập
                doc.SaveAs2(filePath);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Lỗi: {ex.Message}");
            }
        }

    }
}
