
#include<stdio.h>
#include<conio.h>

struct complex
{
	float real, img;
};

struct complex_polar
{
	float r,theta;
}

complex divide ( complex x, complex y)
{
complex z;
z.real=(((x.real*y.real)+(x.img*y.img))/((y.real*y.real)+(y.img*y.img)));
z.img=(((x.img*y.real)-(x.real*y.img))/((y.real*y.real)+(y.img*y.img)));
return z;
}

complex multi ( complex x, complex y)
{
complex z;
z.real=((x.real*y.real)+(x.img*y.img));
z.img=((x.img*y.real)+(x.real*y.img));
return z;
}

/*
Slack Bus	: Idukki (1)

PQ Bus		: Kalamassery (2)
			: Madakathara (3)
			: Brahmapuram (4)

PV Bus		: Sabarigi  (5)
*/

// Bus Names
char bus_name[5][15];
stycpy(bus_name[0],"Idukki");
stycpy(bus_name[1],"Kalamassery");
stycpy(bus_name[2],"Madakathara";
stycpy(bus_name[3],"Brahmapuram");
stycpy(bus_name[4],"Sabarigi");

// Y Matrix

float y[5][5];

//Voltage Matrix
complex V[5];
complex_polar V_polar[5];

// Power Matrix

complex s[5];

//function declatation
void read_data();
void print_data();
void PQ_bus_iteration(int);
void Gauss_Seidel();
void find_P(int);
voidd find_Q(int);
void rect2polar();
void clr();


// main function
void main()
{
	int ;
	clr();
	read_data();
	Gauss_Seidel();
	clr();
	print_data();
}

//reads the real and reactive powers in actual units and converts to pu;
read_data()
{
	for(i=0;<5;i++)
	{
		clr();
		printf("Bus No:\t%i\nBus Name:\t%s\n",i+1,bus_name[i]);
		printf("Enter the data\n");
		printf("P (in MW)\t:");
		scanf("%f",&s[i].real);
		s[i].real/=780;
		if(i==4)
		{
			printf("V (in KV)\t:");
			scanf("%f",&V_polar[i].r);
			V_polar[i].r/=220;
			printf("delta (in degrees)\t:");
			scanf("%f",&V_polar[i].theta);
			V[i].real=V_polar[i].r*cos(V_polar[i].theta*0.017);
			V[i].imag=V_polar[i].r*sin(V_polar[i].theta*0.017);
			continue;
		}
		printf("Q (in MVAR)\t:");
		scanf("%f",&s[i].img);
		s[i].img/=585;
		
	}
	for(i=0;i<4;i++)
	{
		V[i].real=1;
		V[i].img=0;
		V_polar[i].r=1;
		V_polar[i].theta=0;
		
	}
	clr()
}

//displays the data in actual units after conversion from PU
print_data()
{
	for(i=0;i<5;i++)
	{
		printf("Bus No:\t%i\nBus Name:\t%s\n",i+1,bus_name[i]);
		printf("P (in MW)\t:%0.2f\n"s[i].real);
		printf("Q (in MVAR)\t:%0.2f\n"s[i].img);
		printf("V (in KV)\t:%0.2f\n"V_polar[i].r);
		printf("delta (in degrees)\t:%0.2f\n"V_polar[i].theta);
		getch();
	}
}

// this function will calculate the change is voltage fro on PQ bus
void PQ_bus_iteration(int i){
int k;
float b_i=0;
complex temp,y_temp;
for(k=0;k<5;k++)
{
	b_i=b_i+(y[i][k]*V[k].img);
	if(k==i)
		continue;
}
V[i].img=-(V[i].img);
temp=divide(s[i],V[i]);
temp.img=temp.img-b_i;
V[i].img=-(V[i].img);
y_temp.real=0;
y_temp.img=y[i][i];
V[i]=divide(temp,y_temp);
return;
}

// this function will do the iteration part
void Gauss_Seidel()
{
	int i,j;
	
	for(i=0;i<5;i++)
	{
		for(j=1;j<=3,j++)
		{
			PQ_bus_iteration(j);
		}
		rect2polar();
		find_P(0);
		find_Q(0);
		find_Q(4);
	}
	
}

//this fumction will fing the real power for the specified bus
void find_P(int i)
{
	int j;
	s[i].real=0;
	for(j=0;j<5;j++)
	{
		s[i].real=s[i].real+((abs(V_polar[k].r))*(abs(y[i][k]))*((V_polar[i].theta)-(V_polar[k].theta)));
	}
	s[i].real=(s[i].real)*(V_polar[i].r);
}

//this fumction will fing the reactive power for the specified bus
void find_Q(int i)
{
	int j;
	s[i].img=0;
	for(j=0;j<5;j++)
	{
		s[i].img=s[i].img+((abs(V_polar[k].r))*(abs(y[i][k]))*cos(((V_polar[i].theta)-(V_polar[k].theta))*0.017));
		if(k==i)
			continue;
	}
	s[i].img=(s[i].img)*(V_polar[i].r);
	s[i].img=-(s[i].img)+((abs(V_polar[k].r))*(abs(V_polar[k].r))*(abs(y[i][i])))
}

//converts the voltages in rectanglecoordnates to polar coordinates
void rect2polar()
{
	for(int i=0;i<5;i++)
	{
		V_polar[i].r=sqrt(V[i].real*V[i].real+V[i].img*V[i].img);
		V_polar[i].theta=atan(V[i].img/V[i].real)*(57.3)
	}
}

//clears the screeen and puts the title on
void clr()
{
	clrscr();
	printf("\t\t Load Flow Analysis (Kerala)\n");
}

