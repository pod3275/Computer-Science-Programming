use hospital;

SELECT emp.work_year, emp.name
from emp
where (emp.work_year >= 10) AND (emp.id < 201400)
order by emp.work_year;