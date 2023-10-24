#include "db.h"
// ---------------------------------------------
// SNode class
// Default constructor
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 
SNode::SNode():Node(num_students)	// Inherits from Node(num_students) passing num_students as the key
{
first = ""; // An anonymous student added with unknown age and such
last = "";	// Thus the names are blank and the age is zero
age = 0;
num_students += 1;	// It would still count as a student though
}

// Constructor
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 
SNode::SNode(string f_, string l_, unsigned int a_):Node(num_students)	// Inherits from Node passing the num_students as the key
{
    first = f_;	// Give f_ to the first name data member
    last = l_;	// Give l_ to the last name data member
    age = a_;	// Give a_ to the age data member
    num_students += 1;	// Update num_students which is also the ID number to reflect the additonal student
}   
// Destructor
SNode::~SNode()
{
	// Since we did not malloc anything directly we can leave this be
}

unsigned int SNode::num_students = 0;

// Public interface
void SNode::change_first(string f_)
{
    first = f_;	// Set first name to the input string
} 
void SNode::change_last(string l_)
{
    last = l_;	// Set last name to the input string
} 
string SNode::get_first()
{
    return first;
}
string SNode::get_last()
{
    return last;
}
unsigned int SNode::get_age()
{
    return age;
}
// Print information about the student
// do not change this
void SNode::print_info(ostream& to)
{
    to << "Student ID: " << this->get_key()
       << "\tFirst: " << this->first
       << "\tLast: " << this->last
       << "\tAge: " << this->age << endl;
}
// ---------------------------------------------

