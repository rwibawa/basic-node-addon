const mytools = require('./build/Debug/mytools.node');

mytools.writeFile('./test01.txt', 'lorem ipsum dolor sit amet', ( error, result ) => {
  if (error) {
    console.error( error.message || error );
  } else {
    console.debug(`Result: ${JSON.stringify(result)}`);
  }
});

module.exports = mytools;