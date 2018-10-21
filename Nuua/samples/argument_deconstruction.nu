greet = (person) {
    print("This is " + person['name'] + " and he/she is " + person['age'] + " years old")
}

greet2 = ({ name, age }) {
    print("This is " + name + " and he/she is " + age + " years old")
}

greet3 = ([name, age]) {
    print("This is " + name + " and he/she is " + age + " years old")
}

for ({key, value} in { name: 'Erik', age: 21 }) {
    print(key + ": " + value)
}

greet({ name: 'Erik', age: 21})
greet2({ name: 'Erik', age: 21})
greet3(['Erik', 21])
