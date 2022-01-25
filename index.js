const mytools = require('./build/Debug/mytools.node');

const cb = ( error, result ) => {
  if (error) {
    console.error( error.message || error );
  } else {
    console.debug(`Result: ${JSON.stringify(result)}`);
  }
};

mytools.writeFile('./test01.txt', 'lorem ipsum dolor sit amet', cb);

module.exports = mytools;