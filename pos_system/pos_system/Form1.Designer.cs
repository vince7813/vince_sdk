namespace pos_system
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
        /// 修改這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.name = new System.Windows.Forms.Label();
            this.price = new System.Windows.Forms.Label();
            this.number = new System.Windows.Forms.Label();
            this.total = new System.Windows.Forms.Label();
            this.calView = new System.Windows.Forms.DataGridView();
            this.listView = new System.Windows.Forms.DataGridView();
            this.c_name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.c_price = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.textBoxPrice = new System.Windows.Forms.TextBox();
            this.numericUpDownNum = new System.Windows.Forms.NumericUpDown();
            this.textBoxTotal0 = new System.Windows.Forms.TextBox();
            this.g_name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.g_price = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.g_number = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.g_total = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonTotal = new System.Windows.Forms.Button();
            this.textBoxTotal = new System.Windows.Forms.TextBox();
            this.buttonReset = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.calView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.listView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownNum)).BeginInit();
            this.SuspendLayout();
            // 
            // name
            // 
            this.name.AutoSize = true;
            this.name.Font = new System.Drawing.Font("新細明體", 12F);
            this.name.Location = new System.Drawing.Point(57, 49);
            this.name.Name = "name";
            this.name.Size = new System.Drawing.Size(40, 16);
            this.name.TabIndex = 0;
            this.name.Text = "品名";
            // 
            // price
            // 
            this.price.AutoSize = true;
            this.price.Font = new System.Drawing.Font("新細明體", 12F);
            this.price.Location = new System.Drawing.Point(177, 49);
            this.price.Name = "price";
            this.price.Size = new System.Drawing.Size(40, 16);
            this.price.TabIndex = 0;
            this.price.Text = "單價";
            // 
            // number
            // 
            this.number.AutoSize = true;
            this.number.Font = new System.Drawing.Font("新細明體", 12F);
            this.number.Location = new System.Drawing.Point(251, 49);
            this.number.Name = "number";
            this.number.Size = new System.Drawing.Size(40, 16);
            this.number.TabIndex = 0;
            this.number.Text = "數量";
            // 
            // total
            // 
            this.total.AutoSize = true;
            this.total.Font = new System.Drawing.Font("新細明體", 12F);
            this.total.Location = new System.Drawing.Point(328, 49);
            this.total.Name = "total";
            this.total.Size = new System.Drawing.Size(56, 16);
            this.total.TabIndex = 0;
            this.total.Text = "總價錢";
            // 
            // calView
            // 
            this.calView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.calView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.g_name,
            this.g_price,
            this.g_number,
            this.g_total});
            this.calView.Location = new System.Drawing.Point(60, 134);
            this.calView.Name = "calView";
            this.calView.RowTemplate.Height = 24;
            this.calView.Size = new System.Drawing.Size(324, 150);
            this.calView.TabIndex = 1;
            // 
            // listView
            // 
            this.listView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.listView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.c_name,
            this.c_price});
            this.listView.Location = new System.Drawing.Point(548, 82);
            this.listView.Name = "listView";
            this.listView.RowTemplate.Height = 24;
            this.listView.Size = new System.Drawing.Size(244, 215);
            this.listView.TabIndex = 2;
            this.listView.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.listView_CellClick);
            this.listView.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.listView_CellContentClick);
            // 
            // c_name
            // 
            this.c_name.HeaderText = "品名";
            this.c_name.Name = "c_name";
            // 
            // c_price
            // 
            this.c_price.HeaderText = "單價";
            this.c_price.Name = "c_price";
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(60, 82);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(100, 22);
            this.textBoxName.TabIndex = 3;
            // 
            // textBoxPrice
            // 
            this.textBoxPrice.Location = new System.Drawing.Point(180, 81);
            this.textBoxPrice.Name = "textBoxPrice";
            this.textBoxPrice.Size = new System.Drawing.Size(45, 22);
            this.textBoxPrice.TabIndex = 4;
            // 
            // numericUpDownNum
            // 
            this.numericUpDownNum.Location = new System.Drawing.Point(254, 81);
            this.numericUpDownNum.Name = "numericUpDownNum";
            this.numericUpDownNum.Size = new System.Drawing.Size(49, 22);
            this.numericUpDownNum.TabIndex = 5;
            this.numericUpDownNum.ValueChanged += new System.EventHandler(this.numericUpDownPrice_ValueChanged);
            // 
            // textBoxTotal0
            // 
            this.textBoxTotal0.Location = new System.Drawing.Point(331, 81);
            this.textBoxTotal0.Name = "textBoxTotal0";
            this.textBoxTotal0.Size = new System.Drawing.Size(53, 22);
            this.textBoxTotal0.TabIndex = 6;
            // 
            // g_name
            // 
            this.g_name.HeaderText = "品名";
            this.g_name.Name = "g_name";
            // 
            // g_price
            // 
            this.g_price.HeaderText = "單價";
            this.g_price.Name = "g_price";
            this.g_price.Width = 60;
            // 
            // g_number
            // 
            this.g_number.HeaderText = "數量";
            this.g_number.Name = "g_number";
            this.g_number.Width = 60;
            // 
            // g_total
            // 
            this.g_total.HeaderText = "小計";
            this.g_total.Name = "g_total";
            this.g_total.Width = 60;
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(420, 82);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonAdd.TabIndex = 7;
            this.buttonAdd.Text = "加入";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonTotal
            // 
            this.buttonTotal.Location = new System.Drawing.Point(420, 309);
            this.buttonTotal.Name = "buttonTotal";
            this.buttonTotal.Size = new System.Drawing.Size(75, 23);
            this.buttonTotal.TabIndex = 8;
            this.buttonTotal.Text = "總價";
            this.buttonTotal.UseVisualStyleBackColor = true;
            this.buttonTotal.Click += new System.EventHandler(this.buttonTotal_Click);
            // 
            // textBoxTotal
            // 
            this.textBoxTotal.Location = new System.Drawing.Point(284, 309);
            this.textBoxTotal.Name = "textBoxTotal";
            this.textBoxTotal.Size = new System.Drawing.Size(100, 22);
            this.textBoxTotal.TabIndex = 9;
            // 
            // buttonReset
            // 
            this.buttonReset.Location = new System.Drawing.Point(60, 308);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(75, 23);
            this.buttonReset.TabIndex = 10;
            this.buttonReset.Text = "reset";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(826, 371);
            this.Controls.Add(this.buttonReset);
            this.Controls.Add(this.textBoxTotal);
            this.Controls.Add(this.buttonTotal);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.textBoxTotal0);
            this.Controls.Add(this.numericUpDownNum);
            this.Controls.Add(this.textBoxPrice);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.listView);
            this.Controls.Add(this.calView);
            this.Controls.Add(this.total);
            this.Controls.Add(this.number);
            this.Controls.Add(this.price);
            this.Controls.Add(this.name);
            this.Name = "Form1";
            this.Text = "POS點菜系統";
            ((System.ComponentModel.ISupportInitialize)(this.calView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.listView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownNum)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label name;
        private System.Windows.Forms.Label price;
        private System.Windows.Forms.Label number;
        private System.Windows.Forms.Label total;
        private System.Windows.Forms.DataGridView calView;
        private System.Windows.Forms.DataGridViewTextBoxColumn g_name;
        private System.Windows.Forms.DataGridViewTextBoxColumn g_price;
        private System.Windows.Forms.DataGridViewTextBoxColumn g_number;
        private System.Windows.Forms.DataGridViewTextBoxColumn g_total;
        private System.Windows.Forms.DataGridView listView;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_name;
        private System.Windows.Forms.DataGridViewTextBoxColumn c_price;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.TextBox textBoxPrice;
        private System.Windows.Forms.NumericUpDown numericUpDownNum;
        private System.Windows.Forms.TextBox textBoxTotal0;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonTotal;
        private System.Windows.Forms.TextBox textBoxTotal;
        private System.Windows.Forms.Button buttonReset;
    }
}

