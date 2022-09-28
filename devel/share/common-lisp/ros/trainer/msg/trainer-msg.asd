
(cl:in-package :asdf)

(defsystem "trainer-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "LUT" :depends-on ("_package_LUT"))
    (:file "_package_LUT" :depends-on ("_package"))
  ))