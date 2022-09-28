;; Auto-generated. Do not edit!


(when (boundp 'main::LUT)
  (if (not (find-package "MAIN"))
    (make-package "MAIN"))
  (shadow 'LUT (find-package "MAIN")))
(unless (find-package "MAIN::LUT")
  (make-package "MAIN::LUT"))

(in-package "ROS")
;;//! \htmlinclude LUT.msg.html


(defclass main::LUT
  :super ros::object
  :slots (_data ))

(defmethod main::LUT
  (:init
   (&key
    ((:data __data) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _data __data)
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint16[] _data
    (* 2    (length _data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16[] _data
     (write-long (length _data) s)
     (dotimes (i (length _data))
       (write-word (elt _data i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16[] _data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _data (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _data i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;;
   self)
  )

(setf (get main::LUT :md5sum-) "e066daa5966378a57445687eb65bfa3b")
(setf (get main::LUT :datatype-) "main/LUT")
(setf (get main::LUT :definition-)
      "uint16[] data
")



(provide :main/LUT "e066daa5966378a57445687eb65bfa3b")


