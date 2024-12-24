const express = require('express');
const { spawn } = require('child_process');
const fs = require('fs'); // File system module
const cors = require('cors');  
const path = require('path'); // Path module for handling file paths
const app = express();
const port = 3001;

app.use(cors());  
app.use(express.json());  

app.post('/process-dna', (req, res) => {
    const dnaSequence = req.body.dnaSequence;

    if (!dnaSequence) {
        return res.status(400).send('DNA sequence is required');
    }

    console.log('Received DNA sequence:', dnaSequence);

    // Step 1: Create SEQs directory if it doesn't exist
    const seqsDir = path.join(__dirname, 'SEQss'); // Directory SEQs/
    if (!fs.existsSync(seqsDir)) {
        fs.mkdirSync(seqsDir); // Create SEQs directory if it doesn't exist
    }

    // Step 2: Create a unique file name for the .fasta file
    const fileName = `dna_${Date.now()}.fasta`; // Unique file name
    const filePath = path.join(seqsDir, fileName); // Path to the .fasta file in SEQs/

    // Step 3: Write the DNA sequence to the .fasta file in FASTA format
    const fastaContent = `>DNA_sequence\n${dnaSequence}`;
    fs.writeFileSync(filePath, fastaContent, 'utf8');

    console.log('FASTA file created at:', filePath);

    // Step 4: Pass the file path to the C++ executable
    const executablePath = './proccess.exe'; // Path to your C++ executable
    const process = spawn(executablePath, [filePath]); // Pass the SEQs/filePath as an argument
    let output = '';
    let errorOutput = '';

    process.stdout.on('data', (data) => {
        output += data.toString();  // Append the output from stdout
        console.log('C++ stdout:', data.toString());  // Print to Node.js console
    });
    
    process.stderr.on('data', (data) => {
        errorOutput += data.toString();  // Append the error output
        console.error('C++ stderr:', data.toString());  // Print to Node.js console
    });

    process.on('close', (code) => {
        console.log(`C++ program exited with code: ${code}`);
        if (code !== 0) {
            console.error(`Error executing C++ program: ${errorOutput || 'No error output captured'}`);
            return res.status(500).send('Error processing DNA sequence');
        }
    
        console.log('Processed DNA:', output.trim());
        return res.json({ processedDna: output.trim() });
    });
    
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
