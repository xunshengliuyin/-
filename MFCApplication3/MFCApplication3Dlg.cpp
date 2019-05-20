
// MFCApplication3Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#define MAX 1010
#endif
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
void reverse_data(string &data)
{
	char temp = '0';
	int start = 0;
	int end = data.size() - 1;
	assert(data.size() && start <= end);
	while (start < end)
	{
		temp = data[start];
		data[start++] = data[end];
		data[end--] = temp;
	}
}
void compute_value(string lhs, string rhs, string &result)
{
	reverse_data(lhs);
	reverse_data(rhs);
	int i = 0, j = 0, res_i = 0;
	int tmp_i = 0;
	int carry = 0;

	for (i = 0; i != lhs.size(); ++i, ++tmp_i)
	{
		res_i = tmp_i;  //在每次计算时，结果存储的位需要增加
		for (j = 0; j != rhs.size(); ++j)
		{
			carry += (result[res_i] - '0') + (lhs[i] - '0') * (rhs[j] - '0');//此处注意，每次计算并不能保证以前计算结果的进位都消除， 并且以前的计算结果也需考虑。
			result[res_i++] = (carry % 10 + '0');
			carry /= 10;
		}
		while (carry)//乘数的一次计算完成，可能存在有的进位没有处理
		{
			result[res_i++] = (carry % 10 + '0');
			carry /= 10;
		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
	{
		if (result[i] != '0')
			break;
		else
			result.pop_back();
		//result.pop();
	}
	reverse_data(result);
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication3Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication3Dlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedButton1()
{
	CString str, str1 , str2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1);
	GetDlgItem(IDC_EDIT3)->GetWindowText(str2);
   // MessageBox(_T("编辑框内的文本是") + str, NULL, MB_ICONINFORMATION); //显示编辑框文本
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
	//std::string std1, std2;
	string std3;
	string std1 = (CStringA)str1;//.GetBuffer(0);
	string std2 = (CStringA)str2;//.GetBuffer(0);

//	cin >> std1 >> std2;
	int length1 = std1.length();
	int length2 = std2.length();
	int a[MAX] = { 0 };
	int b[MAX] = { 0 };
	int result[2 * MAX] = { 0 };
	int i = 0, j = 0;
	//将字符串转移到数组中，以方便计算 ，注意是倒叙存储
	//即字符串123存为321，为的是将低位放在前面方便计算?
	for (i = length1 - 1, j = 0; i >= 0; i--, j++)
	{
		a[j] = std1[i] - '0';
	}
	for (i = length2 - 1, j = 0; i >= 0; i--, j++)
	{
		b[j] = std2[i] - '0';
	}
	//将结果储存在 resullt中，result[i + j] = a[i] * b[j]是关键算法?
	for (i = 0; i < length1; i++)
	{
		for (j = 0; j < length2; j++)
		{
			result[i + j] = result[i + j] + a[i] * b[j];
		}
	}

	//从低位到高位进行进位

	for (i = 0; i < (length1 + length2); i++)
	{
		if (result[i] > 9)
		{
			result[i + 1] = result[i + 1] + result[i] / 10;
			result[i] = result[i] % 10;
		}
	}
	//将前导0全部剔掉，比如我们结果是236，在result中
	//是这样存储的63200……我们需要定位到第一个不为零的数，它的位置也就是i ，两数相乘，位数最多是两数位数之和

	for (i = length1 + length2; i >= 0; i--)
	{
		if (result[i] == 0) continue;
		else break;
	}
	//接着i继续输出，就是我们的结果?
	for (; i >= 0; i--)
	{
		// result[i];
		std3[i] = result[i] + '0';
	}
	str = std3.c_str();
	
	MessageBox(_T("答案是") + str, NULL, MB_ICONINFORMATION); //显示编辑框文本

}


void CMFCApplication3Dlg::OnEnChangeEdit1()
{

	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	//CString.m_edit1.SetWindowText(_T("ppppppp"));
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
