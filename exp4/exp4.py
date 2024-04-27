import re

# Global variable for generating unique temporary variable names
temp_count = 1

# Function to generate three-address code for assignment
def generate_assignment_code():
    global temp_count
    expression = "a = b * c + d"  # Example expression
    print("Expression:", expression)

    # Split the expression into LHS and RHS
    lhs, rhs = expression.split('=')
    lhs = lhs.strip()
    rhs = rhs.strip()

    # Split the RHS into terms
    terms = rhs.split(' ')
    
    code = []  # List to store generated TAC
    # Generate TAC for operations in the RHS
    for i in range(len(terms)):
        if terms[i] in ['+', '*']:
            op = terms[i]
            operand1 = terms[i - 1]
            operand2 = terms[i + 1]
            temp = f't{temp_count}'
            temp_count += 1
            
            code.append(f"{temp} = {operand1} {op} {operand2};")
            terms[i + 1] = temp  # Update the next operand to use the temporary variable
    
    # Final assignment to the LHS
    code.append(f"{lhs} = {terms[-1]};")
    print("Three-address code:")
    print('\n'.join(code))  # Display generated TAC


# Function to generate three-address code for conditional statements
def generate_conditional_code():
    global temp_count
    expression = "if (a < b) then c = d + e else c = d - e"  # Example conditional expression
    print("Expression:", expression)

    # Extract condition, then-part, and else-part
    parts = re.split(r' then | else ', expression)
    condition = parts[0][3:].strip()  # Remove "if "
    then_part = parts[1].strip()
    else_part = parts[2].strip()

    # Create labels for branching in TAC
    true_label = f'L{temp_count}'
    temp_count += 1
    end_label = f'L{temp_count}'
    temp_count += 1
    
    # Generate TAC for conditional branching
    code = [
        f"if {condition} goto {true_label};",
        f"{else_part} goto {end_label};",
        f"{true_label}: {then_part};",
        f"{end_label}:"
    ]
    print("Three-address code:")
    print('\n'.join(code))  # Display generated TAC


# Function to generate three-address code for copy operations
def generate_copy_code():
    expression = "x = y"  # Example copy expression
    print("Expression:", expression)

    # Split the expression into target and source
    target, source = expression.split('=')
    target = target.strip()
    source = source.strip()

    # Generate TAC for copy operation
    print("Three-address code:")
    print(f"{target} = {source};")  # Display generated TAC


# Function to generate three-address code for indexed assignment
def generate_indexed_assignment_code():
    global temp_count
    expression = "x[2] = y + 5"  # Example indexed assignment expression
    print("Expression:", expression)

    # Extract the array name and index
    target, operation = expression.split('=')
    array_name = target[:target.index('[')].strip()
    index = target[target.index('[') + 1:target.index(']')].strip()

    # Split the operation into parts
    operation_parts = operation.strip().split(' ')
    
    # Generate TAC for indexed assignment
    intermediate_var = f't{temp_count}'
    temp_count += 1
    
    code = [
        f"{intermediate_var} = {operation_parts[0]} {operation_parts[1]} {operation_parts[2]};",
        f"{array_name}[{index}] = {intermediate_var};"
    ]
    print("Three-address code:")
    print('\n'.join(code))  # Display generated TAC


# Main function with menu-driven interaction
def main():
    while True:
        print("Generate three-address code for:")
        print("1. Assignment")
        print("2. Conditional")
        print("3. Indexed Assignment")
        print("4. Copy")
        print("5. Exit")
        
        # Get user input
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            generate_assignment_code()
        elif choice == 2:
            generate_conditional_code()
        elif choice == 3:
            generate_indexed_assignment_code()
        elif choice == 4:
            generate_copy_code()
        elif choice == 5:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please enter a number from 1 to 5.")
        
        print()  # Print a blank line for separation


if __name__ == "__main__":
    main()  # Run the main function to start the program
