use hospital;

select dept.dept_name, emp.name, emp.work_year
from dept, doctor, emp
where dept.officer_id = doctor.doctor_id
	AND doctor.doctor_id = emp.id
order by dept.dept_name;