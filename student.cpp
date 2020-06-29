/*
**	学生信息管理系统
**	IDE：Dev-Cpp 4.9.9.2
**	2014-6-15
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
using std::sort;
using std::vector;
 
/*==存储单元节点==*/
struct student{
	//字符数组方便统一输入
	char name[50], address[100], email[50], id[20],
		age[5], birth[20], tel[20], gender[5];	
};
vector<student> myvec;
/*==========函数声明区==========*/
 
 
/*-打印主菜单声明-*/
void printMainMenu();
 
/*-主界面各函数声明-*/
void enterInformation();  //1
void browseInformation();  //2
void inquireInformation();  //3
void modifyInformation();  //4
void deleteInformation();  //5
void saveToFile();			//6
void readFromFile();		//7
void exitInformation();  //0
 
/*--主界面函数的子函数声明--*/
void inquireOneStudent(student *);
void modifyOneStudent(student *);
 
/*--修改单项信息--*/
void modifyOneId(student *);
void modifyOneName(student *);
void modifyOneAge(student *);
void modifyOneGender(student *);
void modifyOneBirth(student *);
void modifyOneTel(student *);
void modifyOneAddress(student *);
void modifyOneEmail(student *);
void modifyToMain(student *); //这个其实不需要形参，只是为了统一跳转表接口
 
/*--删除一个学生--*/
void deleteOneStudent(student *);
 
/*--显示一个学生的所有信息--*/
void displayOneStudent(student *);
 
/*--浏览方式--*/
void browsePlain(); //直接浏览
void browseById();
void browseByName();
void browseByBirth();
void browseToMain();
 
/*--查询方式--*/
void inquireById();
void inquireByName();
 
/*-函数指针数组-*/
void (*mainPointerArr[])() = {
	exitInformation, enterInformation, 
	browseInformation, inquireInformation,
	modifyInformation, deleteInformation, saveToFile, readFromFile
};
	
void (*modifyOne[])(student *) = {
	modifyToMain, modifyOneId, modifyOneName,
	modifyOneAge, modifyOneGender, modifyOneBirth,
	modifyOneTel, modifyOneAddress, modifyOneEmail
};
 
void (*browseArray[])() = {
	browseToMain, browsePlain, browseById, 
	browseByName, browseByBirth
};
 
/*==========函数定义区==========*/
 
/*-主界面菜单函数-*/
void printMainMenu(){
	printf("\t\t\t河南理工大学学生信息管理系统\n\n");
	printf("\t\t   ======================================\n");
	printf("\t\t  ||\t\t1、学生信息录入 \t||\n");
	printf("\t\t  ||\t\t2、学生信息浏览 \t||\n");
	printf("\t\t  ||\t\t3、学生信息查询 \t||\n");
	printf("\t\t  ||\t\t4、学生信息修改 \t||\n");
	printf("\t\t  ||\t\t5、学生信息删除 \t||\n");	
	printf("\t\t  ||\t\t6、学生信息存档 \t||\n");	
	printf("\t\t  ||\t\t7、学生信息读档 \t||\n");
	printf("\t\t  ||\t\t0、退出管理系统 \t||\n");
	printf("\t\t   ======================================\n");
	printf("\t\t\t\t\t\t原创作者：邱正钢\n");
	printf("\t\t\t\t\t\t完成时间：2014年6月17日\n");
	printf("\t\t\t\t\t\tEmail：2276479303@qq.com\n");
	printf("请选择功能：");
	int num;
	scanf("%d", &num);
	(*mainPointerArr[num])();
}
 
/*-信息录入-*/
void enterInformation(){ //1
	system("cls");
	printf("输入学生信息：\n");
	printf("请输入学号：");
	int len; student temp;
	while(gets(temp.id) && !strlen(temp.id))
		; //过滤缓存回车
	printf("请输入姓名：");
	while(gets(temp.name) && !strlen(temp.name))
		; //过滤缓存回车
	printf("请输入年龄：");
	while(gets(temp.age) && !strlen(temp.age))
		; //过滤缓存回车
	printf("请输入性别：");
	while(gets(temp.gender) && !strlen(temp.gender))
		; //过滤缓存回车
	printf("请输入生日：");
	while(gets(temp.birth) && !strlen(temp.birth))
		; //过滤缓存回车
	printf("请输入电话：");
	while(gets(temp.tel) && !strlen(temp.tel))
		; //过滤缓存回车
	printf("请输入地址：");
	while(gets(temp.address) && !strlen(temp.address))
		; //过滤缓存回车
	printf("请输入Email：");
	while(gets(temp.email) && !strlen(temp.email))
		; //过滤缓存回车
	myvec.push_back(temp);
	system("cls");
	printf("OK,录入成功，该学生信息如下：\n");
	len = myvec.size() - 1;
	inquireOneStudent(&myvec[len]);
}
 
void browseInformation(){  //2
	if(myvec.empty()){
		printf("没有检测到任何学生信息！请在录入后再浏览！\n系统将返回到主界面\n");
		system("pause");
		browseToMain();
	}
	printf("请选择功能：\n");
	printf("1、直接浏览\n");
	printf("2、按学号排序后浏览\n");
	printf("3、按姓名排序后浏览\n");
	printf("4、按生日排序后浏览\n");
	printf("0、返回主菜单\n");
	int num; scanf("%d", &num);
	(*browseArray[num])();
	browseInformation();
}
 
void inquireInformation(){ //3
	if(myvec.empty()){
		printf("没有数据，无法查询！系统将退到主菜单\n");
		system("pause");
		browseToMain();
		return;
	}
	printf("请选择功能：");
	printf("1、输入学号查询\n");
	printf("2、输入姓名查询\n");
	printf("0、返回主菜单\n");
	int num; scanf("%d", &num);
	if(num == 1) inquireById();
	else if(num == 2) inquireByName();
	system("pause");
	browseToMain();
}
 
void modifyInformation(){ //4 
	printf("请输入要更改的学生学号：");
	char buf[20];
	while(gets(buf), !strlen(buf))
		; //依然是过滤空串
	vector<student>::iterator it = myvec.begin();
	for( ; it != myvec.end(); ++it){
		if(strcmp(buf, it->id) == 0){
			modifyOneStudent(&myvec[it - myvec.begin()]);
			return;
		}
	}
	printf("没有找到！\n");
}
void deleteInformation(){  //5
	if(myvec.empty()){
		printf("没有数据可供删除，系统将返回到主菜单。\n");
		system("pause");
		browseToMain();
		return;
	}
	printf("请选择功能：\n");
	printf("1、清空所有数据\n");
	printf("2、删除特定学生的信息\n");
	printf("0、返回主菜单\n");
	int num; scanf("%d", &num);
	if(1 == num){
		myvec.clear();
		printf("成功清除所有信息\n");
		return;
	}else if(2 == num){	
		char buf[20];
		printf("请输入学生学号：");
		while(gets(buf), !strlen(buf))
			;
		vector<student>::iterator it = myvec.begin();
		for( ; it != myvec.end(); ++it){
			if(!strcmp(buf, it->id)){
				deleteOneStudent(&myvec[it - myvec.begin()]); return;
			}
		}
		printf("未找到该学生！\n");
	}
	system("pause");
	browseToMain();
}
void saveToFile(){			//6
	if(myvec.empty()){
		printf("数据为空，无法存储，请在录入信息后再存储到文件！系统将返回到主菜单！\n");
		system("pause"); 
		browseToMain();
		return;		
	}
	FILE *fp = fopen("studentInformation.txt", "w");
	vector<student>::iterator it = myvec.begin();
	for( ; it < myvec.end(); ++it){
		fprintf(fp, "%s\n", it->id);
		fprintf(fp, "%s\n", it->name);
		fprintf(fp, "%s\n", it->age);
		fprintf(fp, "%s\n", it->gender);
		fprintf(fp, "%s\n", it->birth);
		fprintf(fp, "%s\n", it->tel);
		fprintf(fp, "%s\n", it->address);
		fprintf(fp, "%s\n", it->email);
	}
	fclose(fp);
	printf("OK, 存档完成！系统将返回到主界面。\n");
	system("pause"); browseToMain();
}
void readFromFile(){		//7 
	FILE *fp = fopen("studentInformation.txt", "rb");
	if(fp == NULL){
		printf("未检测到存档文件！系统将返回到主界面。\n");
		system("pause");
		browseToMain();
		return;
	}
	student it;
	myvec.clear();
	while(fscanf(fp, "%s", it.id) == 1){
		fscanf(fp, "%s", it.name);
		fscanf(fp, "%s", it.age);
		fscanf(fp, "%s", it.gender);
		fscanf(fp, "%s", it.birth);
		fscanf(fp, "%s", it.tel);
		fscanf(fp, "%s", it.address);
		fscanf(fp, "%s", it.email);
		
		myvec.push_back(it);
	}
	fclose(fp);
	if(myvec.empty()){
		printf("读取存档失败！系统将返回到主界面！\n");
	}else{
		printf("读取存档成功！系统将返回到主界面！\n");
	}
	system("pause");
	browseToMain();
}
void exitInformation(){  //0
	printf("感谢您的使用！再见\n");
	system("pause");
	exit(EXIT_SUCCESS);
}
 
void displayOneStudent(student *stu){
	printf("*****************************\n");
	printf("学号：%s\n", stu->id);
	printf("姓名：%s\n", stu->name);
	printf("年龄：%s\n", stu->age);
	printf("性别：%s\n", stu->gender);
	printf("生日：%s\n", stu->birth);
	printf("电话：%s\n", stu->tel);
	printf("地址：%s\n", stu->address);
	printf("Email：%s\n", stu->email);
	printf("*****************************\n");
}
void inquireOneStudent(student *stu){
	displayOneStudent(stu);
	printf("请选择操作：\n");
	printf("1、更改该学生信息\n");
	printf("2、删除该学生信息\n");
	printf("0、返回主菜单\n");
	int num; 
label:	scanf("%d", &num);
	if(num == 1) modifyOneStudent(stu);
	else if(num == 2) deleteOneStudent(stu);
	else if(num == 0) modifyToMain(stu);
	else goto label;
}
 
void modifyOneStudent(student *stu){  
	system("cls");
	printf("修改当前学生信息：\n");
	printf("1、修改学号\n");
	printf("2、修改姓名\n");
	printf("3、修改年龄\n");
	printf("4、修改性别\n");
	printf("5、修改生日\n");
	printf("6、修改电话\n");
	printf("7、修改地址\n");
	printf("8、修改Email\n");
	printf("0、返回主菜单\n");
	int num; scanf("%d", &num);
	(*modifyOne[num])(stu);
}
 
void modifyOneId(student *stu){
	printf("请输入新的学号：");
	while(gets(stu->id) && !strlen(stu->id))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);	
}
void modifyOneName(student *stu){
	printf("请输入新的姓名：");
	while(gets(stu->name) && !strlen(stu->name))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);	
}
void modifyOneAge(student *stu){
	printf("请输入新的年龄：");
	while(gets(stu->age) && !strlen(stu->age))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);
}
void modifyOneGender(student *stu){
	printf("请输入新的性别：");
	while(gets(stu->gender) && !strlen(stu->gender))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);
}
void modifyOneBirth(student *stu){
	printf("请输入新的生日：");
	while(gets(stu->birth) && !strlen(stu->birth))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);
}
void modifyOneTel(student *stu){
	printf("请输入新的电话：");
	while(gets(stu->tel) && !strlen(stu->tel))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);
}
void modifyOneAddress(student *stu){
	printf("请输入新的地址：");
	while(gets(stu->address) && !strlen(stu->address))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);
}
void modifyOneEmail(student *stu){
	printf("请输入新的Email：");
	while(gets(stu->email) && !strlen(stu->email))
		; //过滤缓存回车
	printf("修改成功！更改后的学生信息如下:\n");
	inquireOneStudent(stu);
}
void modifyToMain(student *stu){
	system("cls");
	printMainMenu();
}
 
void deleteOneStudent(student *stu){
	vector<student>::iterator it;
	it = myvec.begin() + (stu - &myvec[0]);
	myvec.erase(it);
	printf("删除成功！\n");
}
 
/*--cmp函数定义--*/
bool cmpById(student a, student b){
	if(strcmp(a.id, b.id) < 0) return true;
}
bool cmpByName(student a, student b){
	if(strcmp(a.name, b.name) < 0) return true;
}
bool cmpByBirth(student a, student b){
	if(strcmp(a.birth, b.birth) < 0) return true;
}
 
/*--浏览方式--*/
void browsePlain(){ //直接浏览
	if(myvec.empty()){
		printf("数据为空！将返回主菜单。\n");
		system("pause");
		modifyToMain(NULL);
	}
	vector<student>::iterator stu = myvec.begin();
	for( ; stu != myvec.end(); ++stu)
		displayOneStudent(&myvec[stu - myvec.begin()]);	
}
void browseById(){
	if(myvec.empty()){
		printf("数据为空！将返回主菜单。\n");
		system("pause");
		modifyToMain(NULL);
	}
	sort(myvec.begin(), myvec.end(), cmpById);
	vector<student>::iterator stu = myvec.begin();
	for( ; stu != myvec.end(); ++stu)
		displayOneStudent(&myvec[stu - myvec.begin()]);	
}
void browseByName(){
	if(myvec.empty()){
		printf("数据为空！将返回主菜单。\n");
		system("pause");
		modifyToMain(NULL);
	}
	sort(myvec.begin(), myvec.end(), cmpByName);
	vector<student>::iterator stu = myvec.begin();
	for( ; stu != myvec.end(); ++stu)
		displayOneStudent(&myvec[stu - myvec.begin()]);
}
void browseByBirth(){
	if(myvec.empty()){
		printf("数据为空！将返回主菜单。\n");
		system("pause");
		modifyToMain(NULL);
	}
	sort(myvec.begin(), myvec.end(), cmpByBirth);
	vector<student>::iterator stu = myvec.begin();
	for( ; stu != myvec.end(); ++stu)
		displayOneStudent(&myvec[stu - myvec.begin()]);
}
void browseToMain(){
	system("cls");
	printMainMenu();
}
 
/*--查询方式--*/
void inquireById(){
	printf("请输入要查询的学生学号：");
	char buf[20]; int ok = 0;
	while(gets(buf), !strlen(buf))
		; //依然是过滤空串
	vector<student>::iterator it = myvec.begin();
	for( ; it != myvec.end(); ++it){
		if(strcmp(buf, it->id) == 0){
			displayOneStudent(&myvec[it - myvec.begin()]);
			ok = 1;
		}
	}
	if(0 == ok) printf("没有找到！\n");
}
 
void inquireByName(){
	printf("请输入要查询的学生姓名：");
	char buf[20]; int ok = 0;
	while(gets(buf), !strlen(buf))
		; //依然是过滤空串
	vector<student>::iterator it = myvec.begin();
	for( ; it != myvec.end(); ++it){
		if(strcmp(buf, it->name) == 0){
			displayOneStudent(&myvec[it - myvec.begin()]);
			ok = 1;
		}
	}
	if(0 == ok) printf("没有找到！\n");
}
 
 
/*==========主函数==========*/
int main(){
	printMainMenu();
	return 0;
}