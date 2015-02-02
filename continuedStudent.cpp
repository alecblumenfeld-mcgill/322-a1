#include "continued.h"
unsigned int gcd(unsigned int a, unsigned int b){
    if(b==0){
        return a;
    }
    else{
        return gcd(b,a%b);
    }
    
    return 0;
}
unsigned int gcdFaster(unsigned int a, unsigned int b){
    
    
    int c;
    while (a != b) {
        while (a > b) {
            c = a - b;
            a = c;
        }
        while (b > a) {
            c = b - a;
            b = c;
        }
    }
    return a;
    
}
ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
    double x =(double)b/(double)a;
    
    if((int)x <1){
        return NULL;
    }
    ContinuedFraction *result ;
    result = (ContinuedFraction*) malloc (sizeof(ContinuedFraction));
    
    result->head= (int)x;
    
    return result;
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {
    
    ContinuedFraction *x = new ContinuedFraction;
    x->head = 0;
    //generate first part of cf
    x->tail= getCFlargerThanOne(b, a);
    //keep track of this becusethis is what we ultamitly return.
    ContinuedFraction *head = x->tail;
    while (x->tail != NULL) {
        //address the next part of the fraction
        x = x->tail;
        //get remainder
        int r  = b % a;
        //debug ;)
        //std::cout<<b << '%'<< a<<"="<<r<<'\n';
        //swap old denomnator for numerator
        b=a;
        //replace old denmoenator with the remander
        a = r;
        //calculate continued fraction and asign it to the next part of the cf object, like
        //a linked list
        ContinuedFraction *y = getCFlargerThanOne(b, a);
        x->tail = y;
        
  
        
    }
    return head;
}


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
    ContinuedFraction *x = new ContinuedFraction;
    x->head= head;
    x->tail = fixed;
    ContinuedFraction *copy ;
    copy = (ContinuedFraction*) malloc (sizeof(ContinuedFraction));
    copy = period;
    ContinuedFraction *temp = copy;
    while (temp->tail != NULL) {
        temp = temp->tail;
    }
    temp->tail = copy;
    temp= x;
    while (temp->tail != NULL) {
        temp = temp->tail;
    }
    temp->tail = copy;
    
    return x;
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
//    std::cout<<fr->head<<'\n';
//    Fraction *x = new Fraction;
//    if (fr->tail == NULL || n==0) {
//        Fraction *y = new Fraction;
//        y->numerator = 1;
//        y->denominator= fr->head;
//        return *y;
//    }
//    
//    *x = getApproximation(fr->tail, n-1);
//    x->denominator = x->denominator + fr->head;
//
    
    Fraction *x= new Fraction;
    ContinuedFraction *ptr = new ContinuedFraction;
    ptr = fr->tail;
    while(ptr != NULL && n !=0){
     
        n-=1;
        std::cout<<ptr->head<<' ' << n<<'\n';
        x->denominator += ptr->head;
        ptr = ptr->tail;
    }
    x->numerator = 1+ fr->head;
    
    return *x;
    
}


