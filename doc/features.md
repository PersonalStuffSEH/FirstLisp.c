this is where i put potential features my friends and i discuss
$ operator (comments will be changed)
  it goes to the end of the expression and evaluates it backwards to the original $
  (print getName | map upper) -> (print getName) map (upper)
  (print $ getName | map upper) -> (print (upper map getName))
<e operator
  it reverses the control flow
  (monadPrint1 monadPrint2 <e) ->  (monadPrint1 monadPrint2) (monadPrint2 monadPrint1)
? operator (?print "Hello, World!")
  prints the debug info (scope and stuff)
._. partial functions
  (func arg1.arg2.arg3), _ would be that this argument is left blank
  (func 0w0w0w0) or 0 means blank and w means next argument
((func args)?error)
  if func(args) fails raise error
c |=> val
  c = c if c else val
(@var = val)
  var is a computed property depending on val
(\x.x)
  lambdas, like in Haskell
