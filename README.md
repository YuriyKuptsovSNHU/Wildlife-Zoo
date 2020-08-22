# Wildlife-Zoo
C++ Program to Demonstrate C++/Java integration, text file record handling, and class hierarchy definition.

About Wildlife Zoo:
This project showcases integration between C++ and Java via JNI, class hierarchy definition, the use of the factory pattern to instantiate classes, processing of record files with fixed length fields, and robust handling of user input.

I designed a creative way to generate class instances of various types on the fly. The handling of user input was contextually based on the expectations of the instance variable types of classes selected on the basis of user input.

I believe my handing of user input and instantiation of classes based on dynamically changing input was well handled.

Given the opportunity, I would enhance my code by adding additional classes to represent more animal types and subtypes. I would also allow the introduction of unknown animal subtypes. For example, if a subtype of animal were entered by the user, I would handle this with a multipurpose subclass of the parent type specified by the user. In this case, the user would be asked to give more information about the subtype. After gathering that information, and instance of “CustomizedMammal” or “CustomizedOviparous” would be created, the specific information would be stored in the instance, and then the instance would be used to both represent the customized type and as a prototype to clone future instances of the same subtype. In this case, instead of inheritance, new instances would be created, for this customized subtypes, through cloning (copying of the prototype instance and then specializing through specific deviations of additionally added instances).

The factory class was the most challenging, though it is small. It was necessary to be able to instantiate classes based on string names, something that I had not done before in C++. I overcame this challenged by reflecting upon my experience with Java and by using my creativity. I learned quite a lot about Visual C++ in this assignment. I chose Visual C++ to overcome the shortcomings of Eclipse.

My knowledge of C++ classes has grown and I believe it will be highly valuable future course work.

The program is well factored and its various subparts can be easily adapted to other projects. The naming conventions I chose make the code readable.

