#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class item{

  long  ID;
  string Name;
  float Rate;
  long Quantity;
  item* Next;

  public:


      void update_Name(string newname)
      {
          this->Name=newname;
      }
      void update_Rate(float newrate)
      {
          this->Rate=newrate;
      }
      void update_Quantity(long quantity)
      {
          this->Quantity=this->Quantity+quantity;
      }
      string get_Name()
      {
            return Name;
      }
      float get_Rate()
      {
            return Rate;
      }
      long get_Quantity()
      {
            return Quantity;
      }

    friend class Hash_Item;
};

class Hash_Item{

    private:

        int noBucket;
        item **table;

    public:

        Hash_Item()
        {
            this->noBucket=10;
            table= new item*[noBucket];
            for(int i=0 ; i< noBucket ; i++)
                table[i]=NULL;
        }

        int HashFunction(long data)
        {
            return (data%noBucket);
        }

        void ItemInsert(long id, string name,float rate, long quantity)
        {
            int index=HashFunction(id);
            item* temp1;
            temp1=table[index];
            item* temp=new item;
            temp->ID=id;
            temp->Name=name;
            temp->Rate=rate;
            temp->Quantity=quantity;

            
            if(table[index]==NULL)
            {
                temp->Next=NULL;
                table[index]=temp;
            }
            else
            {
                 if(temp1->Next==NULL)
                 {
                     if(temp1->ID>temp->ID)
                     {
                         temp->Next=temp1;
                         table[index]=temp;
                     }
                     else
                     {
                         temp1->Next=temp;
                         temp->Next=NULL;
                     }
                 }
                 else
                 {
                     if(temp->ID<temp1->ID)
                     {
                         temp->Next=temp1;
                         table[index]=temp;
                     }
                   else
                   {
                     while( temp1->Next!=NULL && temp->ID>=temp1->Next->ID )
                     temp1=temp1->Next;

                     if(temp1->Next==NULL)
                     {
                         temp1->Next=temp;
                         temp->Next=NULL;
                     }
                     else
                     {
                         temp->Next=temp1->Next;
                         temp1->Next=temp;
                     }
                   }
                 }

            }
        }

        void Display()
        {
            item* temp1;
            for(int i=0; i<noBucket ; i++)
            {
                if(table[i]!=NULL)
                {
                    temp1=table[i];

                    while(temp1->Next!=NULL)
                    {
                        cout<<temp1->ID<<" ---> ";
                        temp1=temp1->Next;
                    }

                cout<<temp1->ID<<endl;
                }
            }
        }

        item* ItemSearch(long id)
        {
            int index=HashFunction(id);
            item* temp;

            if(table[index]!=NULL)
            {
                temp=table[index];

                while(temp!=NULL && temp->ID!=id )
                    temp=temp->Next;
            }

            if(temp==NULL || table[index]==NULL)
                return NULL;
            else
                return temp;

        }

        long ItemDelete(long id)
        {
            int index=HashFunction(id);
            item* temp1;
            temp1=table[index];

            if(table[index]==NULL)
            {
               return 0;
            }
            else
            {
                 if(temp1->Next==NULL)
                 {
                     if(temp1->Next->ID==id)
                     {
                         table[index]=NULL;
                         return id;
                     }
                     else
                        return 0;
                 }
                 else
                 {
                        if(temp1->ID==id)
                        {
                           table[index]=temp1->Next;

                        }
                         else
                         {
                             while(temp1->Next->ID!=id && temp1!=NULL)
                                temp1=temp1->Next;

                             if(temp1==NULL)
                                return 0;
                             else
                             {
                                 temp1->Next=temp1->Next->Next;
                                 return id;
                             }
                         }
                 }
            }
        }

};


class Inventory: public item,public Hash_Item
{

    private:
    Hash_Item Item_list;

    protected:

        void Add_item(long id,string name,float rate, long quantity)
        {
            Item_list.ItemInsert(id,name,rate,quantity);
        }

        void Delete_item(long id)
        {
           int a=Item_list.ItemDelete(id);
           if(a==0)
            cout<<"item was not Found Please check Item_Id again";
        }

        void update_item(long id,float newrate)
        {
            item* temp=Item_list.ItemSearch(id);

                 if(temp!=NULL)
                temp->update_Rate(newrate);
                else
                    cout<<"This item is not available now";

        }
        public:

        void update_stock(long id,long quantity)
        {
            item* temp=Item_list.ItemSearch(id);

                if(temp!=NULL)
                    temp->update_Quantity(quantity);
                else
                    cout<<"This item is not available now";

        }

        string get_Product_Name_Info(long id)
        {
            item* temp=Item_list.ItemSearch(id);
            return  temp->get_Name();


        }
        float get_Product_Rate_Info(long id)
        {
            item* temp=Item_list.ItemSearch(id);
            return temp->get_Rate();
        }
        long get_Product_Quantity_Info(long id)
        {
            item* temp=Item_list.ItemSearch(id);
            return temp->get_Quantity();
        }


        void Display_Product_Info(long id)
        {
            item* temp=Item_list.ItemSearch(id);

           if(temp!=NULL)
           {
            string name=temp->get_Name();
            float rate=temp->get_Rate();
            long quantity=temp->get_Quantity();

            cout<<"Item_ID        :"<<id<<endl;
            cout<<"Item_Name      :"<<name<<endl;
            cout<<"Item_rate      :"<<rate<<endl;
            cout<<"Item_Quantity  :"<<quantity<<endl<<endl;
           }
           else
            cout<<"Not Found please check your itemID";
        }

 friend class Manager;
};

Inventory inventory;

class customer{

  long  ID;
  string Name;
  double Points;
  customer* Next;

  public:


      string get_Name()
      {
            return Name;
      }

      double get_Points()
      {
            return Points;
      }
      void set_Points(float points)
      {
            this->Points=points;
      }

     friend class Hash_customer;
     friend class Billing;
};

class Hash_customer{

    private:

        int noBucket;
        customer **table;

    public:

        Hash_customer()
        {
            this->noBucket=10;
            table= new customer*[noBucket];
            for(int i=0 ; i< noBucket ; i++)
                table[i]=NULL;
        }

        int HashFunction(long data)
        {
            return (data%noBucket);
        }

        void customerInsert(long id, string name,double points)
        {
            int index=HashFunction(id);
            customer* temp1;
            temp1=table[index];
            customer* temp=new customer;
            temp->ID=id;
            temp->Name=name;
            temp->Points=0;

            
            if(table[index]==NULL)
            {
                temp->Next=NULL;
                table[index]=temp;
            }
            else
            {
                 if(temp1->Next==NULL)
                 {
                     if(temp1->ID>temp->ID)
                     {
                         temp->Next=temp1;
                         table[index]=temp;
                     }
                     else
                     {
                         temp1->Next=temp;
                         temp->Next=NULL;
                     }
                 }
                 else
                 {
                     if(temp->ID<temp1->ID)
                     {
                         temp->Next=temp1;
                         table[index]=temp;
                     }
                   else
                   {
                     while( temp1->Next!=NULL && temp->ID>=temp1->Next->ID )
                     temp1=temp1->Next;

                     if(temp1->Next==NULL)
                     {
                         temp1->Next=temp;
                         temp->Next=NULL;
                     }
                     else
                     {
                         temp->Next=temp1->Next;
                         temp1->Next=temp;
                     }
                   }
                 }

            }
        }

        void Display()
        {
            customer* temp1;
            for(int i=0; i<noBucket ; i++)
            {
                if(table[i]!=NULL)
                {
                    temp1=table[i];

                    while(temp1->Next!=NULL)
                    {
                        cout<<temp1->ID<<" ---> ";
                        temp1=temp1->Next;
                    }

                cout<<temp1->ID<<endl;
                }
            }
        }

        customer* customerSearch(long id)
        {
            int index=HashFunction(id);
            customer* temp;

            if(table[index]!=NULL)
            {
                temp=table[index];

                while(temp!=NULL && temp->ID!=id )
                    temp=temp->Next;
            }

            if(temp==NULL || table[index]==NULL)
                return NULL;
            else
                return temp;

        }


};

class customer_List:public Hash_customer,public customer
{

    private:

    Hash_customer customerlist;

    public:

    void Add_customer(long id, string name,double points)
    {
        customerlist.customerInsert(id,name,0);
    }

     int  update_points(long id,double newpoints)
      {
          customer* temp=customerlist.customerSearch(id);

          if(temp!=NULL)
          {
            temp->set_Points(temp->get_Points()+newpoints);
            return 1;
          }
          else return 0;
      }

      customer* find_customer(long id)
      {
          customer* temp=customerlist.customerSearch(id);

          if(temp!=NULL)
            return temp;
          else
            return NULL;
      }

     void Display_customer_Info(long id)
        {
            customer* temp=customerlist.customerSearch(id);

           if(temp!=NULL)
           {
            string name=temp->get_Name();
            float points=temp->get_Points();

            cout<<"Customer_ID        :"<<id<<endl;
            cout<<"Customer_Name      :"<<name<<endl;
            cout<<"Customer_points    :"<<points<<endl<<endl;

           }
           else
            cout<<"Not Found please check your itemID";
        }


};


class Manager:public Inventory
{

    private:

    long ID;
    string Name;

    public:


    Manager(long id,string name)
    {
        this->ID=id;
        this->Name=name;
    }

    void upload_items(long id,string name,float rate, long quantity)
    {
        inventory.Add_item(id,name,rate,quantity);
    }

    void remove_items(long id)
    {
        inventory.Delete_item(id);
    }

    void update_item(long id,float newrate)
    {
        inventory.update_item(id,newrate);
    }
    void update_stock(long id,long newstock)
    {
        inventory.update_stock(id,newstock);
    }

    void Display_Product_Info(long id)
    {
        inventory.Display_Product_Info(id);
    }
    long  getManagerId()
    {
        return ID;
    }

    string getManagerName()
    {
        return Name;

    }


};

class item1{

    private:

        long ID;
        string Name;
        float Rate;
        long Quantity;
        double amount;
        item1* Next;

    public:

        void setAmount()
        {
            this->amount=Rate*Quantity;
        }

        double getAmount()
        {
            return this->amount;
        }

    friend class Billing;
    friend class item1_list;
};

class item1_list{

     public:

      item1* head,*tail;


        item1_list()
        {
            head=NULL;
            tail=NULL;
        }


    void Insert_Item1(long id,string name, float rate, long quantity)
    {
            item1* temp=new item1;
            temp->ID=id;
            temp->Name=name;
            temp->Rate=rate;
            temp->Quantity=quantity;
            temp->setAmount();

            temp->Next=NULL;
            if(head==NULL)
            {
                head=temp;
                tail=temp;
            }
            else
            {
                tail->Next=temp;
                tail=temp;
            }

    }

    int delet_Item1(long id)
    {
            item1* temp;
            temp=head;
            if(head->ID==id)
            {
                head=head->Next;
                return id;
            }
            else
            {
                while(temp->Next->ID!=id)
                    temp=temp->Next;
                if(temp->Next==tail)
                    tail=temp;
                else
                    temp->Next=temp->Next->Next;
                return id;
            }

    }

    void display()
    {

        item1* temp;
        temp=head;
         cout<<"Item_Id              Item_Name        Rate       Quantity     Amount"<<endl<<endl;
        while(temp!=NULL)
        {
                
                printf("%-21ld",temp->ID);
                cout<<temp->Name;
                 printf("%20.2f %8ld %15.2f\n",temp->Rate,temp->Quantity,temp->amount);

                temp=temp->Next;
        }
    }

    item1* ItemSearch(long id)
    {
        item1* temp;
        temp=head;

        while(temp!=NULL && temp->ID!=id )
        temp=temp->Next;

        if(temp!=NULL)
            return temp;
        else
            return NULL;
    }

};
class Billing:public customer_List
{

    private:

    long Customer_id;
    item1_list itemlist;

    public:

        static int Transaction_Id;
        double Total_amount;



        void Buy_item(long id,long quantity)
        {
            if(inventory.get_Product_Quantity_Info(id)>0)
            {
                string name=inventory.get_Product_Name_Info(id);
                int rate=inventory.get_Product_Rate_Info(id);
                itemlist.Insert_Item1(id,name,rate,quantity);
                inventory.update_stock(id,-(quantity));
            }
            else
                cout<<"Stock is empty";

        }

        void Cancle_item(long id, long quantity)
        {
           item1* temp=itemlist.ItemSearch(id);
           int newQuantity=temp->Quantity-quantity;
           inventory.update_stock(id,temp->Quantity);
           itemlist.delet_Item1(id);
           if(newQuantity>0)
           Buy_item(id,newQuantity);
        }

        double getTotal_Amount()
        {
            item1* temp;
            temp=itemlist.head;
            this->Total_amount=0;

            while(temp!=NULL)
            {
                this->Total_amount=this->Total_amount+temp->amount;
                temp=temp->Next;
            }
            return this->Total_amount;
        }

        void asign_customerID(long id)
        {
            Customer_id=id;
            int temp=update_points(Customer_id,getTotal_Amount());
            if(temp==0)
            {
                string name;
                cin>>name;
                Add_customer(Customer_id,name,0);
                temp=update_points(Customer_id,getTotal_Amount());
            }
        }

        void make_payment()
        {
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<endl;
            Transaction_Id=Transaction_Id+1;
            cout<<"Transaction_Id       :"<<" "<<Transaction_Id<<endl;
            cout<<"Customer_Id          :"<<" "<<Customer_id<<endl<<endl;

            itemlist.display();
            cout<<endl;

            double total=getTotal_Amount();
            cout<<"                                            Total Amount :   ";
            printf("%.2f\n\n",total);
            cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl<<endl;
        }
        
        void Refresh_Itemlist()
        {
            itemlist.head=NULL;
        }

};

int Billing::Transaction_Id=0;




int main()
{

    Manager Harsh(201901016,"Harsh");

    Billing Agent;

    long INVENTORY_DATASET[100][4] = {
{111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},
{111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
{111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
{111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
{111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
{222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
{222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
{222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
{222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
{222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
};
    
    long CUSTOMER_DATASET[100][3] = {
{9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
{9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
{9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
{9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
{9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
{9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
{9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
{9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
{9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
{9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
};


    string productnames[100];
    string customernames[100];

    for(int i=0 ; i<100 ; i++)
    {
        productnames[i]=to_string(INVENTORY_DATASET[i][1]);
    }
    for(int i=0 ; i<100 ; i++)
    {
        customernames[i]=to_string(CUSTOMER_DATASET[i][1]);
    }

    for(int i=0; i<100 ; i++)
    {
        Harsh.upload_items(INVENTORY_DATASET[i][0],to_string(INVENTORY_DATASET[i][1]),INVENTORY_DATASET[i][2],INVENTORY_DATASET[i][3]);
    }

    for(int i=0; i<100 ; i++)
    {
        Agent.Add_customer(CUSTOMER_DATASET[i][0],to_string(CUSTOMER_DATASET[i][1]),CUSTOMER_DATASET[i][2]);
    }

    //*****For first transaction *****//
    Agent.Buy_item(111100000011,3);
    Agent.Buy_item(222200001114,1);
    Agent.Buy_item(222200001234,2);
    
    Agent.asign_customerID(9400000011);
    
    Agent.make_payment();
    // Harsh is a manager, and Agent is Biling object
    
    Harsh.Display_Product_Info(111100000011);
    Harsh.Display_Product_Info(222200001114);
    Harsh.Display_Product_Info(222200001234);
    Agent.Display_customer_Info(9400000011);
    
    Agent.Refresh_Itemlist();
    cout<<endl<<endl;
     //*****For second transaction *****//
    
    Agent.Buy_item(111100000011,3);
    Agent.Buy_item(222200001114,4);
    Agent.Buy_item(222200001234,6);
    
    Agent.asign_customerID(9400000057);
    
    Agent.make_payment();
    // Harsh is a manager, and Agent is Biling object
    
    Harsh.Display_Product_Info(111100000011);
    Harsh.Display_Product_Info(222200001114);
    Harsh.Display_Product_Info(222200001234);
    Agent.Display_customer_Info(9400000057);
    
    Agent.Refresh_Itemlist();
    
    
    
   
}