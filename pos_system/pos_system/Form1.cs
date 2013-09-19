using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace pos_system
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            DataGridViewRowCollection rows = listView.Rows;
            rows.Add(new Object[] { "紅茶", 25 });
            rows.Add(new Object[] { "綠茶", 20 });
            rows.Add(new Object[] { "奶茶", 35 });
        }

        private void listView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void listView_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            textBoxName.Text = listView.Rows[e.RowIndex].Cells[0].Value.ToString();
            textBoxPrice.Text = listView.Rows[e.RowIndex].Cells[1].Value.ToString();
            numericUpDownNum.Value = 1;
            textBoxTotal0.Text = textBoxPrice.Text;
        }

        private void numericUpDownPrice_ValueChanged(object sender, EventArgs e)
        {
            decimal total;
            total=numericUpDownNum.Value * (Convert.ToInt32(textBoxPrice.Text));
            textBoxTotal0.Text = total.ToString();
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            DataGridViewRowCollection rows = calView.Rows;
            rows.Add(new object[] { textBoxName.Text, textBoxPrice.Text, numericUpDownNum.Value, textBoxTotal0.Text });
        }

        private void buttonTotal_Click(object sender, EventArgs e)
        {
            int c= calView.RowCount-1;
            int total=0;
            for(int i=0;i<c;i++)
            {
                total+=Convert.ToInt32(calView.Rows[i].Cells[3].Value.ToString());
            }
            textBoxTotal.Text = total.ToString();
               
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            calView.Rows.Clear();
        }
    }
}
