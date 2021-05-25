//*******kernelization file***********

#ifndef Kernelization_H
#define Kernelization_H

#include <vector>//for vectors
#include <string>



class Kernelization
{
			
public:
	std::vector<std::vector<double>> dataset;
	std::vector<std::vector<double>> traindata;
	std::vector<std::vector<double>> testdata;
	std::vector<double> X1,X2,X3,Y;//three attributes and the class attribute
	std::vector<double> X_P;//will store values of X1^p1,x2^p2 and X3^p3
	double p1,p2,p3;//will store ethe values of pearson coefficient correlation for three attrubtes
	std::vector<std::vector<double>> kinput;//attributes x1^p1,x2^p2,x3^p3
	
	double alpha = 0.001;//learning rate
	std::vector<double> weight{0.2,0.2,0.2};//nitialized with random values 
	std::vector<std::vector<double>> weightvalues;//storing w1,w2,w3 for each iteration
	double e = 2.71828;//logarithmic e
	
	 



	  double nrmlZD(double val);//for data normalization		
    void readfile(const std::string _filename);//read in data set file and load data
    double PrsnCorCoeff(std::vector<double>& x,std::vector<double>& y,int n);//pearson correlation coefficient
    void expFunc(std::vector<std::vector<double>> input);//function to calculate values of X1^p1,x2^p2 and X3^p3
    void stratifydata();//stratify data into train,test
    void sortdata();//sorting attributes 
	  double sigmoid(double z);//lolss function
   	void updateWeight(double pvalue, double expectedval, std::vector<double> values);//weight update gradient descent
   	void LogisticRegression();//logistic regression
   	void showresults();//to dsiplay results
	
	
    
    


		
};//end of class


#endif   
//*********end of Kernelization*********
