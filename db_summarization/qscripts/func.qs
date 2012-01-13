
// the returned functions should have three arguments: generic params and two-dimensional coordinates
// x - ranged [0, 1], as a second dimension
// y - full-ranged, as a first dimension
(function fConstructor(type, params)
{
     function trapezoid(params, x, y)
      {
          var a = params[0];
          var b = params[1];
          var c = params[2];
          var d = params[3];
          if (x >= b && x <= c) {
              return 1;
          } else if (x > a && x < b) {
              return 1.0 / (b - a) * x + 1.0 - (1.0 / (b - a)) * b;
          } else if (x > c && x < d) {
              return 1.0 / (c - d) * x + 1.0 - (1.0 / (c - d)) * c;
          } else {
              return 0;
          }
      }

    var localParams = params.slice();
    switch (type) {
        case 'trapezoid':
            return function(x, y) {
                return trapezoid(localParams, x, y);
            };
            break;
        case 'bylyfyztsyf':
            return function() {
                return 1;
            };
            break;
        default:
            return function() {
                return 0;
            };
    }
})

