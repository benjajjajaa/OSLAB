// Student Grade Evaluator in C#

Console.WriteLine("Student Grade Evaluator");
Console.WriteLine("-----------------------\n");

// Ask for student name
Console.Write("Enter student name: ");
string? name = Console.ReadLine();

if (string.IsNullOrEmpty(name))
{
    Console.WriteLine("Name cannot be empty.");
    return;
}

// Ask for grade
Console.Write("Enter student grade (0 - 100): ");
string? gradeInput = Console.ReadLine();

if (!int.TryParse(gradeInput, out int grade))
{
    Console.WriteLine("Invalid grade input.");
    return;
}

// Determine grade result
string result;

if (grade >= 90 && grade <= 100)
    result = "Excellent";
else if (grade >= 80)
    result = "Very Good";
else if (grade >= 70)
    result = "Good";
else if (grade >= 60)
    result = "Passed";
else if (grade >= 0)
    result = "Failed";
else
{
    Console.WriteLine("Grade must be between 0 and 100.");
    return;
}

// Display result
Console.WriteLine("\nStudent Result");
Console.WriteLine("--------------");
Console.WriteLine($"Name  : {name}");
Console.WriteLine($"Grade : {grade}");
Console.WriteLine($"Status: {result}");

// Pause before exit
Console.WriteLine("\nPress any key to exit...");
Console.ReadKey();
