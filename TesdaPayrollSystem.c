#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct emp{
	char empName[32];
	char empCode[10];
	int salaryLevel;
	float rate;	
}Employee;

typedef struct week{
	char day[10];
	char holiday[5];
	char timeIn[10];
	char timeOut[10];
	char otTimeIn[10];
	char otTimeOut[10];
}Week;

typedef struct{
	char date[32];
	int workHours;
	int overtimeHours;
	float regIncome;
	float otIncome;
	float tax;
	float sss;
	float gross;
	float net;
}Report;

void generateEmployees();
void displayRecord(Employee);
void displayReport(Report);
void writeReport(Week timecard);
Employee findEmployee(Employee empRecord[4],char code[10]);

int main(void){
	Employee empRecord[4],employee;
	Week timecard[5] = { {"Monday"," "," "," "," "," "},{"Tuesday"," "," "," "," "," "}
						,{"Wednesday"," "," "," "," "," "},{"Thursday"," "," "," "," "," "}
						,{"Friday"," "," "," "," "," "} };
	Report report;
	
	char code[10];
	int i,regTemp;
	float temp;
	
	//Generate Employee.txt file
	//and Read Employee.txt file functions
	generateEmployees();
	FILE *fp = fopen("employee.txt","r");
	fread(&empRecord,sizeof(Employee),4,fp);
	fclose(fp);

	//Program Start
	//Find employee record
	printf("************ Payroll System v1.0 ************\n");
	printf("Please enter your employee code:");
	gets(code);
	employee = findEmployee(empRecord,code);
	fflush(stdin);
	
	//Get timein and out data and date covered
	printf("\n**** Please enter this week's time report ****\n");
	
	for(i=0;i<5;i++){
		printf("*** Report for %s ***\n",timecard[i].day);
		printf("Time-In:");
		scanf("%s",&timecard[i].timeIn);
		printf("Time-Out:");
		scanf(" %s",&timecard[i].timeOut);
		printf("*** Is %s a holiday?(Yes/No):",timecard[i].day);
		scanf(" %s",&timecard[i].holiday);
		printf("*** Overtime ***\nTime-In:");
		scanf(" %s",&timecard[i].otTimeIn);
		printf("Time-Out:");
		scanf(" %s",&timecard[i].otTimeOut);
		fflush(stdin);		
	}
	printf("\nPlease enter date covered:");
	gets(report.date);
	
	//Calculations
	report.workHours = 0;
	report.overtimeHours = 0;
	temp = 0.00;
	regTemp = 0;
	
	for(i=0;i<5;i++){
		// Input of hours
		report.overtimeHours += atoi(timecard[i].otTimeOut) - atoi(timecard[i].otTimeIn);
		
		if(atoi(timecard[i].timeIn) > 12){
			regTemp = ( (12 - atoi(timecard[i].timeIn)) + (atoi(timecard[i].timeOut) - 12)); 
		}else{
			regTemp = ( (12 - atoi(timecard[i].timeIn)) + (atoi(timecard[i].timeOut) - 12) - 1 ); 	
		}

		
		// If it is a Holiday
		if( strcmp(timecard[i].holiday,"Yes") == 0 ){
			report.overtimeHours += regTemp;
			
		}else{ // Not a holiday
			report.workHours += regTemp;
			temp += regTemp * (employee.rate/8);
		}
	}
	
	report.regIncome = temp;
	report.otIncome = report.overtimeHours * ((employee.rate/8)*1.1);
	report.gross = report.regIncome + report.otIncome;
	report.tax = report.gross * .10;
	if(employee.salaryLevel == 1){
		report.sss = report.gross * .01;
	}else if(employee.salaryLevel == 2){
		report.sss = report.gross * .015;
	}else{
		report.sss = report.gross * .02;
	}
	report.net = (report.gross - report.tax) - report.sss;
	
	// Display employee record and weekly salary report
	displayRecord(employee);
	displayReport(report);
	
	for(i=0;i<5;i++){
		writeReport(timecard[i]);
	}

	printf("\ndtr.txt successfully created!");

	return 0;
}

void displayRecord(Employee record){
		printf("\n********* Employee Details *********\n");
		printf("Employee Name: %s\n",record.empName);
		printf("Employee Code: %s\n",record.empCode);
		printf("Salary Level: Level %d\n",record.salaryLevel);
		printf("Salary Rate: Php %.2f/day\n",record.rate);	
		printf("************************************\n");
}

void generateEmployees(){
	Employee empRecord[4] = { {"Juan Santiago","A02-0001",1,380.00},{"Peter Palabrica","A02-0003",3,550.00},
							{"Anthony Almirante","A02-0004",1,380.00},{"Emmie Fukada","A02-0005",2,450.00}};
	FILE *fp = fopen("employee.txt","w+");
	
	fwrite(empRecord,sizeof(Employee),4,fp);
	
	fclose(fp);
}

void displayReport(Report report){
	printf("Date Covered: %s\n",report.date);
	printf("Total Number of Work Hours: %d Hrs.\n",report.workHours);
	printf("Overtime Hours: %d Hrs.\n",report.overtimeHours);
	printf("Regular Income: Php %.2f\n",report.regIncome);
	printf("Overtime Income: Php %.2f\n",report.otIncome);
	printf("Gross Income: Php %.2f\n",report.gross);
	printf("Deductions:\n");
	printf("*Tax: Php %.2f\n",report.tax);
	printf("*SSS: Php %.2f\n",report.sss);
	printf("Net Income: Php %.2f\n",report.net);
	printf("************************************\n");	
}

void writeReport(Week timecard){
	FILE *fp = fopen("dtr.txt","a+");
	
	fwrite(&timecard,sizeof(Week),1,fp);
	
	fclose(fp);
}

Employee findEmployee(Employee empRecord[4],char code[10]){
	Employee ret;
	int i,flag = 0;
	
	for(i=0 ; i<4 && flag != 1 ; i++){
		if( strcmp(empRecord[i].empCode,code) == 0 ){
			ret = empRecord[i];
			flag = 1;
		}
	}
	
	if(flag == 0){
		printf("Employee not found!");
		exit(1);
	}
	
	return ret;
}





