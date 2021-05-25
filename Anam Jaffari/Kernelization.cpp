//*********Kernelization.cpp file ************
//*********(using Haberman survival dataset, link:(https://archive.ics.uci.edu/ml/datasets/haberman's+survival)
#include"Kernelization.h"
#include<iostream>//input output stream
#include<fstream>//for file handling
#include<sstream>//for string stream
#include<string>//for using string
#include<math.h>//round and sqrt
#include<algorithm>//for sort()





    //funtion to normalize the data
    double Kernelization::nrmlZD(double val)
    {
        double max=83.0;
        double min=0.0;
        val= ((val-min)/double(max-min));
        //std::cout<<val<<std::endl;
        return val;

    }
   
//function to read in the file and store values
void Kernelization::readfile(const std::string _filename){
	
	std::fstream Kfile(_filename); //opening the dataset file
	std::vector<double> input;
		
	
	    if (Kfile.is_open())//file open check
        {
            std::string line;
            while(!Kfile.eof())
            {
            	
                             			          				
					
				while(getline(Kfile,line))
                {
                	input.clear();
					std::stringstream ss(line);
				    std::string token;
                    
                   
                    getline(ss,token,',');
                    input.push_back(nrmlZD(std::stod(token)));
                    getline(ss,token,',');
                    input.push_back(nrmlZD(std::stod(token)));
					getline(ss,token,',');
					input.push_back(nrmlZD(std::stod(token)));
					getline(ss,token,'\n');// last col(class col)
					{
						if(token=="2")//binary conversion
						token="0";
					}
					input.push_back(std::stod(token));
					//Y.push_back(std::stod(token));
					dataset.push_back(input); 
									
					
                
				}//end while 
				//dataset.push_back(input); 
					
            }//end outer while
            
        }//end if
        
        
			Kfile.close();//closing the file


		std::cout<<"datasetsize:(with ratio 73% belong to class 1 and 26% belong to class 0): "<<dataset.size()<<std::endl;
		
		
       
}//end function


//function to calculate values of X1^p1,X2^p2 and X3^p3
void Kernelization::expFunc(std::vector<std::vector<double>> input)
{
	//std::cout<<input.size()<<std::endl;
	for(int i=0;i<input.size();i++)
		for(int j=0;j<input[i].size();j++)
			{
			
			X1.push_back(input[i][j]);
			j++;
			X2.push_back(input[i][j]);
			j++;
			X3.push_back(input[i][j]);
			j++;
			Y.push_back(input[i][j]);
			}

	//std::cout<<X1.size()<<"  "<<X2.size()<<"    "<<X3.size()<<"      "<<Y.size()<<std::endl;


	p1=PrsnCorCoeff(X1,Y,X1.size());
	
	p2=PrsnCorCoeff(X2,Y,X2.size());
	
	p3=PrsnCorCoeff(X3,Y,X3.size());
	
	for(int i=0;i<X1.size();i++)
		{
	
		X_P.push_back(pow(X1[i],p1));
		X_P.push_back(pow(X2[i],p2));
		if(X3[i]==0)
		X3[i]=1;
		X_P.push_back(pow(X3[i],p3));
		
		kinput.push_back(X_P);
		X_P.clear();
	
		}

		/*std::cout<<"values of X1^p1, X2^p2 and X3^p3:"<<std::endl;
		for(int i=0;i<kinput.size();i++){
			for(int j=0;j<kinput[i].size();j++)
			std::cout<<kinput[i][j]<<"     ";
			std::cout<<std::endl;
		}*/

}


// function that returns the val of Pearson correlation coefficient
double Kernelization::PrsnCorCoeff(std::vector<double> &x,std::vector<double> &y,int n)
{
	

	double corr; 
    double sumofX = 0.0, sumofY = 0.0, sumofXY = 0.0;
    double squareSumofX = 0.0, squareSumofY = 0.0;
 
    for (int i = 0; i < n; i++)
    {
        // sum of elements of array X.
        sumofX = sumofX + x[i];
 
        // sum of elements of array Y.
        sumofY = sumofY + y[i];
 
        // sum of x[i] * y[i].
        sumofXY = sumofXY + x[i] * y[i];
 
        // sum of square of array elements.
        squareSumofX = squareSumofX + x[i] * x[i];
        squareSumofY = squareSumofY + y[i] * y[i];
    }
 
    // formula for calculating pearson coeff corr
    	 corr = (double)(n * sumofXY - sumofX * sumofY)
                  / sqrt((n * squareSumofX - sumofX * sumofX)
                      * (n * squareSumofY - sumofY * sumofY));
 
    return corr;
}

//function to stratify the data (73% for class 1,and 26% for class 0)
//traindata(157 class 1 and 57 class 0)
//testdata(67 class 1 and 25 class 0)

void Kernelization::stratifydata()
{
	int count1=0;
	int count0=0;
	for (int i=0;i<dataset.size();i++)
		 {
		 
         	if(dataset[i][3]==1){
			    count1++;
         		if(count1<=157)//157 instances for class 1
         		traindata.push_back(dataset[i]);
         		else//67 instances for class 1
         		testdata.push_back(dataset[i]);
				 }
         		
         	else{
			 
         		count0++;
         		if(count0<=57)//57 instances for class 0
         		traindata.push_back(dataset[i]);
         		else//25 instances for class 0
         		testdata.push_back(dataset[i]);
				 }
         	
         	
         	         	
    }//end for
        std::cout<<"stratification:"<<std::endl;
//std::cout<<"training data points:"<<traindata.size()<<"   (73%->class1,26%->classM), test datapoints:  "<<testdata.size()<<"   (73%->classB,26%->classM)"<<std::endl;
	std::cout<<"train data size: (with ratio 73% belong to class 1 and 26% belong to class 0)  "<<traindata.size()<<std::endl;
	std::cout<<"test data size:(with ratio 73% belong to class 1 and 26% belong to class 0)    "<<testdata.size()<<std::endl;
}//end function




//sorting attributes of data 
 void Kernelization::sortdata()
 {
    for (int i=0;i<traindata.size();i++)
	 	//for(int j=0;j<traindata[i].size();j++) 
     		//{
     		std::sort(traindata.begin(),traindata.end());	
			 //} 
    
	
	 for (int i=0;i<testdata.size();i++)
	 	for(int j=0;j<testdata.size();j++) 
     		{
     		std::sort(testdata.begin(),testdata.end());	
			 }
   
	      
 }//end function
 
 
 
 
 
void Kernelization::LogisticRegression() 
{

  	double predictedValue, z = 0;
	  long totalCorrect = 0, totalCases = kinput.size();

  for(int i = 0; i < kinput.size(); i++)
   {
    
    	for(int j = 0; j < kinput[0].size(); j++)
	 	{
      		z += kinput[i][j] * weight[j];
    	}

    	predictedValue = sigmoid(z);

    	updateWeight(predictedValue,Y[i],kinput[i]);

		if(predictedValue < 0.5) {
      predictedValue = 0;
    }
    else {
      predictedValue = 1;
    }

    if(predictedValue == Y[i]) {
      totalCorrect++;
    }

  }
  
  std::cout<<"Accuracy is: "<<(totalCorrect * 100) / totalCases<<"%"<<std::endl;  
	
  
}
//end function


//sigmoid function
double Kernelization::sigmoid(double z)
 	{
  return 1/(1 + pow(e, (-1 * z)));
	}


//updating weights and gradient descent
void Kernelization::updateWeight(double pValue, double expectedval, std::vector<double> values)
 {
  for(int i = 0; i < values.size(); i++) {
    double gradientDescent;
    gradientDescent = (pValue - expectedval) * values[i];
    weight[i] = weight[i] - (alpha * gradientDescent);
  }
  weightvalues.push_back(weight);
}





//show results
void Kernelization::showresults()
{
	
	expFunc(traindata);
	
	std::cout<<"val of p1:"<<p1<<std::endl;
	std::cout<<"val of p2:"<<p2<<std::endl;
	std::cout<<"val of p3:"<<p3<<std::endl;
	LogisticRegression();
	

	std::cout<<"weight values w1,w2,w3"<<std::endl;
	
	for(int i=0;i<weightvalues.size();i++)
	{
	
		for(int j=0;j<weightvalues[i].size();j++)
			{
			
			std::cout<<weightvalues[i][j]<<"  ";
			}
		std::cout<<std::endl;
	}
}


//************END*****************************


