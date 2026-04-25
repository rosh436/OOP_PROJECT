#include <iostream>
using namespace std;

//Hotel management system
//1.Person, 2.guest, 3. Employee, 4. Manager, 4. Room, 5.Booking, 
//  6. Payment, 7.CashPayment, 8.CardPayment, 9.OnlinePayment 
// 10. Bill 11. RoomBill, 12.ServiceBill

class AUsers{
	public:
		virtual void displayDetails() const = 0;
		virtual string getRole() const = 0;
		virtual bool login(string Email, string pass) const = 0;
		virtual bool logOut() = 0;
};

class Person : public AUsers{
	protected:
		string name;
		string number;
		string email;
		int id;
		string password;
		
	public:
		Person(){
			name = "";
			number = "";
			email = "@gmail.com";
			id = 0;
			password ="";
		}
		Person(string n,string no,string e,int ID, string passKey) : name(n),number(no), email(e), id(ID), password(passKey){}
		
		void displayDetails() const override  {
			cout<<"Name: "<<name<<endl;
			cout<<"Number: "<<number<<endl;
			cout<<"Email: "<<email<<endl;
			cout<<"ID: "<<id<<endl;
		}
		
		void setContact(string Email, string num){
			number = num;
			email = Email;
		}
		
		virtual string getRole() const = 0;
		
		bool login(string Email , string pass)const override {
			return(email == Email && pass == password);
		}
		bool logOut() override {
			cout<<"Log out successfull"<<endl;
			return true;
		}
		
		
};

class Guest : public Person{
	protected:
		bool isVip;
		int bookingCount;
		string address;
		string nationality;
		
	public:
		Guest(): isVip(false), bookingCount(0), address(""), nationality("") {}
		Guest(string n, string no, string e, int ID, string pass, string add, string nation):Person(n,no,e,ID,pass), isVip(false), bookingCount(0),address(add), nationality(nation){}
		
		string getRole()const override {
			return "Guest";
		}
		
		bool login(string Email, string pass)const override {
			return(email==Email && password==pass);
		}
		bool logOut(){
			cout<<"Logged out"<<endl;
			return true;
		}
		
		void displayDetails() const{
			Person::displayDetails();
			cout<<"Address: "<<address;
			cout<<"Total number of bookings: "<<bookingCount<<endl;
			cout<<"Nationality: "<<nationality<<endl;
			if(isVip){
				cout<<"Guest is listed as a VIP"<<endl;
			}else{
				cout<<"Guest is not listed as a VIP"<<endl;
			}
		}
		
		void addBooking(){
			bookingCount++;
		}
		
		bool getVIPStatus(){
			if(bookingCount>5){
				cout<<"Discount applicable"<<endl;
				return true;
			}else{
				return false;
			}
		}
		
		void cancelBooking(){
			if(bookingCount>0){
				bookingCount--;
			}else{
				cout<<"You have no prior bookings to cancel"<<endl;
			}
		}
		
		int getBookingCount(){
			return bookingCount;
		}

};

class Employee :  public Person{
	protected:
		string department;
		double salary;
		string shift; //time
		int hoursWorked;  //in a week
		double bonus;
		
	public:
		Employee() : department(""), salary(0), shift(""), hoursWorked(0), bonus(0) {}
		
        Employee(string n, string no, string e, int ID, string p, string d, double s, string sh) : Person(n, no, e, ID, p),
        department(d), salary(s), shift(sh), hoursWorked(0), bonus(2) {}
        
        string getRole() const override {
        	return "Employee";
		}
		
		void displayDetails() const{
			Person::displayDetails();
			cout<<"Department: "<<department<<endl;
			cout<<"Salary: "<<salary<<endl;
			cout<<"Shift: "<<shift<<endl;
			cout<<"Hours worked: "<<hoursWorked<<endl;
			cout<<"Bonus: "<<bonus<<endl;
		}
		
		double calculatePay(){
			return (bonus * hoursWorked) + salary; 
		}
		
		void updatesalary(double NewSalary){
			salary = NewSalary;
		}
	
};

class Room{
	private:
		int roomNumber;
		string type;   //single, double, suite
		double pricePerNight;
		bool isAvailable;
		
	public:
		
		Room() {}

        Room(int num, string t, double price) : roomNumber(num), type(t), pricePerNight(price), isAvailable(true) {}
        
        int getRoomNumber()  {
        	return roomNumber;
		}
		double getPrice() const {
			return pricePerNight;
		}
		bool getAvailability(){
			return isAvailable;
		}
		string getType(){
			return type;
		}
		
		bool bookRoom(){
			if(isAvailable){
				cout<<"Room can be booked"<<endl;
				isAvailable = false;
			}else{
				cout<<"Room is already booked"<<endl;
			}
		}
		
		void displayroom () const {
			cout<<"---Room Details---"<<endl;
			cout<<"Room number: "<<roomNumber<<endl;
			cout<<"Type: "<<type<<endl;
			cout<<"Price per night: "<<pricePerNight<<endl;
			if(isAvailable){
				cout<<"The room is available"<<endl;
			}else{
				cout<<"Room is already booked"<<endl;
			}
		}

};


class Manager : public Employee{
	private:
		int accessLevel;
		
	public:
		Manager(): Employee(), accessLevel(0){}
		
		Manager(string n, string no, string e, int ID, string p, string d, double s, string sh, int al) : Employee(n, no, e, ID, p, d, s, sh), accessLevel(al) {}
		
		string getRole() const override {
			return "Manager";
		}
		
		void displayDetails() const{
			Employee::displayDetails();
			cout<<"Access level: "<<accessLevel<<endl;
		}
		
		void setAccessLevel(int acc){
			accessLevel = acc;
		}
};


class Bill{  //abstract class
	protected:
		double baseAmount;
		double taxRate;
		double discount;
		string status;
	public:
		Bill(double a){
			baseAmount = a;
			taxRate = 0.1;
			discount = 0;
			status = "unpaid";
		}
		
		virtual double calculateTotal() const = 0;
		virtual void displayBill() const = 0;
		
		void applyDiscount(double d){
		    discount = d;
		}
		
		void statusPaid(){
			status = "paid";
		}
		//adding two bills together
		double operator+(const Bill &other) const {
            return calculateTotal() + other.calculateTotal();
        }
		virtual ~Bill(){}  //virtual destructor
};
class RoomBill: public Bill{
	private:
		int days;
		double costPerNight;
	public:
		RoomBill(int d, double price): Bill(0), days(d), costPerNight(price){}
		
	    double calculateTotal() const override{
	    	double total = days*costPerNight;
	    	total += total * taxRate;
	    	total -= discount;
	    	return total;
		}
		
		void displayBill() const override{
			cout << "Room charges: " <<days*costPerNight<<endl;
			cout << "Total(inclusive of tax/discounts): "<< calculateTotal()<<endl;
		}
};
class ServiceBill: public Bill{
	private:
		double serviceCost;
	public:
		ServiceBill(double cost): Bill(cost), serviceCost(cost){}
		
		double calculateTotal() const override{
			double total = serviceCost;
			total += total*taxRate;
			total -= discount;
			return total;
		}
		
		void displayBill() const override{
			cout<< "Service Charges: "<< serviceCost<<endl;
			cout << "Total (with tax/discount): "<< calculateTotal()<<endl;
		}
};
class Booking;
class Payment{
	protected:
		int paymentID;
		double amount;
		string status;
		
	public:
		
		Payment(int id, double amt) : paymentID(id), amount(amt), status("Pending") {}
        
        friend void linkPayment(Booking &b, Payment &p);
        
        bool operator>(const Payment &other) const {
            return amount > other.amount;
        }
        bool operator==(const Payment &other) const {
            return paymentID == other.paymentID;
        }
        
        virtual void processPayment() = 0;   //polymorphism
         
        virtual void displayPayment() const = 0;
         
};

class CashPayment: public Payment{
	public:
		CashPayment(int id, double a): Payment(id, a){}   //the status isnt initiaalized here, cus it is already initialized in the payment constructor, so here the payment constructor runs first, initializing the status as "Pending"
		
		void processPayment() override{
			status = "Completed (Cash).";
			cout << "Processing the cash payment of amount: "<< amount <<endl;
		}
		void displayPayment() const override{
			cout<< "Payment id : " << paymentID<< endl;
			cout<< "Amount : " << amount<<endl;
			cout<< "Status : " <<status<< endl;
		}
};
class OnlinePayment: public Payment{
	public:
		OnlinePayment(int id, int a): Payment(id, a){}
		
		void processPayment() override{
			status = "Completed (online).";
			cout << "Processing the online payment of amount: "<< amount <<endl;
		}
		void displayPayment() const override{
			cout<< "Payment id : " << paymentID<< endl;
			cout<< "Amount : " << amount<<endl;
			cout<< "Status : " <<status<< endl;
		}
};
class CardPayment: public Payment{
	public:
		CardPayment(int id, int a): Payment(id, a){}
		
		void processPayment() override{
			status = "Completed (card).";
			cout << "Processing the card payment of amount: "<< amount <<endl;
		}
		void displayPayment() const override{
			cout<< "Payment id : " << paymentID<< endl;
			cout<< "Amount : " << amount<<endl;
			cout<< "Status : " <<status<< endl;
		}
};
class Booking{
	private:
		int bookingID;
		Guest *guest;
		Room room;
		int days;
	    RoomBill *bill;
	    ServiceBill *serviceBills[10];
	    int serviceCount;
	    Payment *payment;
		
	public:
		Booking() : bookingID(0), guest(NULL), days(0), bill(NULL), serviceCount(0), payment(NULL) {
            for(int i = 0; i < 10; i++) serviceBills[i] = NULL;
        }

        Booking(int id, Guest* g, Room r, int d) : bookingID(id), guest(g), room(r), days(d), serviceCount(0), payment(NULL) {
        	bill = new RoomBill(d, r.getPrice());
        	
        	if(guest->getVIPStatus()){
        		bill->applyDiscount(d*r.getPrice()*0.2);
			}
			guest->addBooking();
			for(int i= 0; i<10; i++){
				serviceBills[i] = NULL;
			}
		}
        friend void linkPayment(Booking &b, Payment &p);
        void addService(double serviceCost){
        	if(serviceCount < 10){
        		serviceBills[serviceCount] = new ServiceBill(serviceCost);
        		serviceCount++;
			} 
			else{
				cout<<"Maximum services reached"<<endl;
			}
		}
		
        double calculateTotal() const {
            double total = bill->calculateTotal();
            for(int i = 0; i < serviceCount; i++){
                total += serviceBills[i]->calculateTotal();
            }
            return total;
        }
		
		void displayBooking() const{
			cout<<"Booking ID: "<<bookingID<<endl;
			cout<<"Guest details: "<<endl;
			guest->displayDetails();
			
			cout<<"Room Details: "<<endl;
			room.displayroom();
			
			cout<<"Room bill"<<endl;
			bill->displayBill();
			
			if(serviceCount > 0){
				cout<<"Service bills: "<<endl;
				for(int i = 0; i< serviceCount; i++){
					serviceBills[i]->displayBill();
				}
			}
			cout<<"Grand total: "<<calculateTotal()<<endl;
		}
		//comparing bookings byy total costs
        bool operator>(const Booking &other) const {
            return calculateTotal() > other.calculateTotal();
        }
        bool operator==(const Booking &other) const {
            return bookingID == other.bookingID;
        }
        
		Guest *getGuest(){
			return guest;
		}
		Room getRoom() const {
			return room;
		}
		
		~Booking(){
			delete bill;
			for(int i = 0; i< serviceCount; i++){
				delete serviceBills[i];
			}
		}

};

void linkPayment(Booking &b, Payment &p){
	b.payment =&p;
	p.status= "linked";
	cout << "Payment is successfully linked to Booking." <<b.bookingID<<endl;
}
int main(){
	
	
	
	
	return 0;
}
