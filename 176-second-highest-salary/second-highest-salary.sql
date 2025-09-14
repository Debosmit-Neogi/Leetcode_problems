# Write your MySQL query statement below
# CASE WHEN COUNT(1) > 0 THEN 1 ELSE 0 END AS [Value]

SELECT 
  MAX(Salary) AS SecondHighestSalary
FROM 
  Employee
WHERE 
  Salary < (SELECT MAX(Salary) FROM Employee);
