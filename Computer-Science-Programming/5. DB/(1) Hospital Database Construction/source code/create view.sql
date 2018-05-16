USE hospital;

CREATE VIEW PATIENT_IN_DEPT (dept_name, num_patient) AS
	SELECT DEPT.dept_name, COUNT(*)
    FROM PATIENT, DOCTOR, DEPT
    WHERE (PATIENT.doctor_id = DOCTOR.doctor_id) 
			AND (DOCTOR.dept_name = DEPT.dept_name)
	GROUP BY DEPT.dept_name;

CREATE VIEW DEPT_ROOM (dept_name, num_room) AS
	SELECT dept_name, COUNT(*)
    FROM ROOM, NURSE
    WHERE ROOM.nurse_id = NURSE.nurse_id
    GROUP BY dept_name;

CREATE VIEW PATIENT_CONDITION AS
	SELECT patient_name, p_condition
    FROM SURGERY, surge_res, PATIENT
    WHERE (SURGERY.surgery_num = SURGE_res.surgery_num)
			AND (SURGERY.patient_RRN = PATIENT.RRN)
	ORDER BY patient_name;
    
CREATE VIEW SURGERY_DEPT (surgery_name, dept_name, doctor_name) AS
	SELECT surgery_name, DEPT.dept_name, EMP.name
    FROM SURGERY, DOCTOR, DEPT, EMP
    WHERE (SURGERY.surgery_num = DOCTOR.surgery_num)
			AND (DOCTOR.dept_name = DEPT.dept_name)
            AND (DOCTOR.doctor_id = EMP.id)
	ORDER BY surgery_name;
    
CREATE VIEW DOCTOR_SURGERY_CONDITION (doctor_name, avg_condition) AS
	SELECT e.name, AVG(sr.p_condition)
    FROM EMP AS e, DOCTOR AS d, SURGERY AS s, SURGE_RES AS sr
    WHERE (e.id = d.doctor_id)
			AND (s.surgery_num = d.surgery_num)
            AND (s.surgery_num = sr.surgery_num)
    GROUP BY e.name
    ORDER BY sr.p_condition;