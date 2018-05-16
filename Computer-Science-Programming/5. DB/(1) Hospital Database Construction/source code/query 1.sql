USE hospital;

SELECT p_condition, patient_name
FROM surge_res, PATIENT, surgery
WHERE (surge_res.surgery_num = surgery.surgery_num)
	AND (surgery.patient_RRN = patient.RRN)
    AND (surge_res.p_condition > 5);